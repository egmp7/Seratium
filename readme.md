# Seratium

Seratium is a DJ application capable of reading .mp3 and .wav files. The decks control music playback with cues, volume faders, and speed controllers. A crossfader controls the main mix of the decks. Timers and titles have been implemented to give users tracking tools and enhance the user experience. The playlist persists data, allows loading tracks to the decks for convenience, and has a search component that looks for items stored in the playlist.

<br>

![Seratium](Assets/Seratium.png)

# Install Seratium IOS

Download and install the [Seratium Package](https://github.com/egmp7/Seratium/releases/download/music/Seratium.pkg).

# Source Files Hierarchy 

1. Assets (png images)
2. Source
    1. Utilities
        1. CSV.h
        2. Format.h
    2. Models
        1. TrackEntry.h
    3. Controllers
        1. DJAudioPlayer.h
    4. Components
        1. DeckComponents
            1. WaveformDisplay.h
            2. DeckAnimation.
            3. Volume.h
            4. Speed.h
            5. CurrentTime.h
            6. RemainingTime.h
            7. CueButton.h
            8. LoadButton.h
            9. PlayPauseButton.h
            10. TrackName.h
        2. Playlist.h
        3. Crossfader.h
    5. GUIs
        1. MainGUI.h
        2. DeckGUI.h
        3. FaderLookAndFeel.h
    6. Main.cpp
    7. MainComponent.h

# Application functionality

## Load a file

There are three options to load a file:

1. By clicking the load button and picking up a file from the pop-up menu
2. Drag and drop a file from a main window
3. Drag and drop a file from the playlist

Each option invokes the controller DJAudioPlayer load method that receives a URL argument. This method creates a reader source for the AudioTransportSource class which allows controlling the audio. 

```
void DJAudioPlayer::loadURL(URL audioURL)
{
    // Audio Format Reader
    auto * reader = formatManager.createReaderFor(
        audioURL.createInputStream(
            URL::InputStreamOptions (URL::ParameterHandling::inAddress)
                .withConnectionTimeoutMs (1000)
                .withNumRedirectsToFollow (0)));
    
    if (reader != nullptr) // good file
    
    {
        // Audio Format Reader Source
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader,true));
    
        // Transport Source
        transportSource.setSource(newSource.get(),0,nullptr,reader->sampleRate);
        
        readerSource.reset(newSource.release());
    }
}
```
## Two track playback

The MainComponent.h creates an instance of the MixerAudioSource Class which receives one or more Audio Sources pointers and mix them together. This happens during the audio life cycle specified by the JUCE framework.

```
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // delegate to DJAudioPlayer
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    // plug sources into the mixer
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}
```
## Volume Component

The volume components on each deck set the volume properties of the crossfader. Then the crossfader component sets the gain property of the AudioTransportSource depending on the crossfader value. 

```
void Volume::sliderValueChanged(Slider* slider)
{
    if(getComponentID() == "volLeft")
        crossfader->setVolumeL(slider->getValue());
    if(getComponentID() == "volRight")
        crossfader->setVolumeR(slider->getValue());
}
```

## Speed Component

Each Deck has access to an instance of the controller DJAudioPlayer, allowing communication between the GUI and the controller. The ResamplingAudioSource is instantiated in DJAudioPlayer and possesses
the ResamplingRatio property that varies the speed of the track. The Speed component sets the ResamplingRatio between 0.5 and 1.5 with a slider listener. Similar to the MixerAudioSource, the resamplingAudioSource uses the audio life cycle to send the output information.

```
void Speed::sliderValueChanged(Slider* slider)
{
    player->setSpeed(slider->getValue());
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio < 0 || ratio > 100.0)
    {
        cout << "DJAudioPlayer::setSpeed setSpeed should be between 0 and 100.0"<< endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}
```

## Animation disk

The AnimatedAppComponent class provides Draw and Update methods to animate elements. The deck animation is a turntable and contains two ellipses, a line, and a path. The ellipses are static and add ornament to the graphic. However, the state of the line and the path instances changes every frame per second depending on the track’s position. This component knows about the controller DJAudioPlayer and gets its position in the Update method. The algorithms animateX and animateY return the ellipse's points responding to the local position variable. The animation algorithm is referenced from the JUCE Animation Tutorials.

```

void DeckAnimation::paint (Graphics& g)
{
    int size = min(getLocalBounds().getWidth(),getLocalBounds().getHeight());
    float responsiveSize = (float) size * 0.009f;
     
    g.fillAll(Colour(36, 17, 51));
    
    // bigger circle
    int d1 = 100 * responsiveSize;
    g.setColour(Colours::black);
    g.fillEllipse(getWidth()/2 - d1/2, getHeight()/2 -d1/2, d1, d1);
    
    // small circle
    int d2 = 40 * responsiveSize ;
    g.setColour(Colour(213,210,255));
    g.fillEllipse(getWidth()/2 - d2/2, getHeight()/2 -d2/2, d2, d2);
    
    // deck line animation
    int pointRadius1 = 50 * responsiveSize;
    int pointRadius2 = 20 * responsiveSize;
    
    Point<float> startPoint (animateX(pointRadius1 , 0), animateY(pointRadius1 , 0));
    Point<float> endPoint   (animateX(pointRadius2 , 0), animateY(pointRadius2 , 0));
    
    g.setColour (Colour(137,70,205));
    g.drawLine(Line<float>(startPoint, endPoint),3.0f);
     
    // ring deck animation
    
    int ringRadius = 50 * responsiveSize;
    auto numberOfDots = 62 ;
    Path path;

    // i = 2 to offset the start of the path
    for (auto i = 2; i < numberOfDots; ++i)
    {
        // get points
        Point<float> p (animateX(ringRadius, i),animateY(ringRadius, i));

        if (i == 2)     // start
            path.startNewSubPath (p);
        else            // add points to Path
            path.lineTo (p);
    }

    g.strokePath (path, PathStrokeType (3.0f));
    
}

void DeckAnimation::update ()
{
    float pos = player->getPosition();
    if(position != pos && !isnan(pos))
        position = pos;
}

float DeckAnimation::animateX (float radius, int offset)
{
    // math to animate a point or varius depending on offset
    return (float)getWidth()  / 2.0f + (float) radius * (-std::sin ((float) position * 1.5f + (float) offset * 0.10f));
}

float DeckAnimation::animateY (float radius, int offset)
{
    // math to animate a point or varius depending on offset
    return (float) getHeight() / 2.0f + (float) radius * std::cos ((float) position * 1.5f + (float) offset * 0.10f);
}
```
## Crossfader Component

This component instantiates a slider that listens and sets the output gain of both decks, depending on the state of their Volume components. Every move on the volume faders or the crossfader itself triggers the mixVolumesAlgorithm(). The algorithm is a linear function that once the crossfader slider reaches the middle state, the sound of both decks will be at its peak. If the slider keeps moving towards any direction, one of the decks gain value will linearly decrease until it reaches 0.

```
void Crossfader::mixVolumesAlgorithm()
{
    float crossfaderValue = crossfaderSlider.getValue();
    
    if(crossfaderValue < 0.5f)
    {
        mainVolumeL = volumeL;
        mainVolumeR = volumeR * (2.0f * crossfaderValue);
    }
    else{
        mainVolumeL = volumeL * (-2.0f * crossfaderValue + 2.0f);
        mainVolumeR = volumeR;
    }
    player1->setGain(mainVolumeL);
    player2->setGain(mainVolumeR);
}
```

## Playlist Component
### Adding files to the playlist

The playlist stores files in the local vector<TrackEntry> playlist, by drag and drop. The FileDragAndDropTarget JUCE class allows this functionality with the filesDropped() method. Once the files are dropped, they pass through a filter that checks if a file’s path already exists in the vector. A new instance of the model Track Entry is created and pushed to the playlist vector when the file is new, otherwise is ignored. 

### Displaying meta data

The TrackEntry model class contains the metadata that displays on the playlist. The properties are the file itself, name, extension, full path, and track length. Almost all the metadata can be originated with the File JUCE class, except the track length. The DJAudioPlayer that instantiates the AudioTransportSource has access to the track length. Therefore, the playlist requires a pointer to the DJAudioPlayer to get the track length from the AudioTransportSource. 

```
void Playlist::filesDropped (const StringArray &files, int x, int y)
{
    for (String file : *&files)
    {
        // check if file exists in playlist
        if (!checkFileInPlaylist(file))
        {
            // prepare player
            player.loadURL(URL{File{file}});
            
            // create a new file
            TrackEntry track{
                File{file},
                File{file}.getFileNameWithoutExtension(),
                File{file}.getFileExtension(),
                File{file}.getFullPathName(),
                (float)player.getTrackLength()};
            
            playlist.push_back(track);
            player.releaseResources();
        }
    }
}
```

### Search functionality

The search functionality requires two vectors. The vector<TrackEntry> playlist stores all the files, and the vector<TrackEntry> playlistView stores the searched file items. The playlistView vector gets rendered in the playlist table. The playlist vector mutates when loading new tracks or when starting the application. While the playlist view mutates when typing in the search box. The TextEditor::Listener class has been implemented in the playlist to listen to the changes in the text editor when typing in the search box. This class contains the textEditorTextChanged() method, which passes an argument that allows the evaluation of the files stored in the playlist vector with the text from the text editor.


```
void Playlist::textEditorTextChanged (TextEditor & textEditor)
{
    playlistView.clear();
    
    // search in playlist
    for (TrackEntry track : playlist)
    {
        if(track.file.getFileName().containsIgnoreCase(textEditor.getText()))
        {
            playlistView.push_back(track);
        }
    }
    
    tableComponent.updateContent();
}
```
### Persisting data

A CSV file is the method to persist data in Seratium. A static property references the playlist vector when dropping files into the playlist. The vector becomes a local static property in the CSV class. Then, a save method stores each TrackEntry property in a line of the CSV. The playlist file is saved in the Music/Seratium directory. The CSV class contains a method to load the data from the CSV file that gets called in the constructor of the Playlist class. 

```
void CSV::save()
{
    fstream file;
    file.open(CSV::playlistPath, ios::out);
    
    if (file.is_open())
    {
        String playlistString;
        
        for (TrackEntry track : *playlist)
        {
            playlistString += createLine(track) + "\n";
        }
        
        // save
        file<< playlistString;
    }
    else
        cout << "CSV::save File not open!" <<endl;

    file.close();
}

vector<TrackEntry> CSV::read()
{
    vector<TrackEntry> entries;
    string line;
    
    fstream file;
    file.open(CSV::playlistPath, ios::in);
        
    if(file.is_open())
    {
        while(getline(file, line))
        {
            // push files
            entries.push_back(stringsToTrackEntry(tokenise(line, ',')));
        }
    }
    else
        cout << "CSV::read File not open!" <<endl;
    
    file.close();
    
    return entries;
}
```

## GUI Layout

### Main GUI

The MainGUI.h class is implemented to separate the structure of the MainComponent.h and establish the MainGUI class only for GUI’s layout purposes. The MainGUI contains the logo, custom graphics, crossfader, playlist, and two DeckGUI components. Each component of the DeckGUI.h has been separated into a component class. 

### LookAndFeel

The FaderLookAndFeel class extends LookAndFeelClass which gives the instruments to customize sliders. I draw sticks to simulate a fader feeling and I switch the custom slider with a .png image file.

```
void FaderLookAndFeel::drawLinearSlider(Graphics &g,
                                                   int _x,
                                                   int _y,
                                                   int _width,
                                                   int _height,
                                                   float _sliderPos,
                                                   float _minSliderPos,
                                                   float _maxSliderPos,
                                                   const Slider::SliderStyle _sliderStyle,
                                                   Slider &_slider)
{
    // reference component elements
    x = &_x;
    y = &_y;
    width = &_width;
    height = &_height;
    sliderPos = &_sliderPos;
    sliderStyle = _sliderStyle;
    slider = &_slider;
    
    // draw custom slider
    // lines
    g.setColour(Colours::white);
    for (Rectangle<int> line : lines())
        g.drawRect(line);
    // background
    g.setColour(Colour(22, 17, 35));
    g.fillRoundedRectangle(backgroundRectangle(), 2.0f);
    // track
    g.setColour(Colour(137,70,205));
    if(FaderStyle::FullGrow == faderStyle)
        g.fillRoundedRectangle(trackRectangle(), 2.0f);
    if(FaderStyle::MidGrow == faderStyle)
        g.fillRect(trackRectangle());
    // thumb
    g.drawImage(thumbImage, thumbRectangle(),RectanglePlacement());
            
}
```