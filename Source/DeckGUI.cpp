/*
  ==============================================================================

    DeckGUI.cpp
    Created: 12 Jan 2023 7:05:21pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 Crossfader* _crossfader,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse,
                 Deck _deck)
:
player(_player),
crossfader(_crossfader),
waveformDisplay(formatManagerToUse, cacheToUse, _player),
volume(_crossfader),
speed(_player),
deckAnimation(_player),
deck(_deck)
{
    // playPause button
    addAndMakeVisible(playPauseButton);
    playPauseButton.addListener(this);
    playPauseButton.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/playPause.png")),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);

    // cue button
    addAndMakeVisible(cueButton);
    cueButton.addListener(this);
    cueButton.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/cue.png")),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);

    // load button
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/load.png")),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);


    // components
    addAndMakeVisible(volume);
    if(deck == Deck::Left)
        volume.setComponentID("volLeft");
    if(deck == Deck::Right)
        volume.setComponentID("volRight");
    addAndMakeVisible(speed);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(deckAnimation);
    addAndMakeVisible(timeTracker);
    addAndMakeVisible(currentTime);

    // Timer class
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
}

void DeckGUI::resized()
{
    double x = getWidth() / 12;
    double y = getHeight() / 12;
    
    // GUI Components               x           y           width       height
    loadButton.setBounds            (x,         0,          x,          y);
    waveformDisplay.setBounds       (x,         y,          x * 10,     y * 2);
    timeTracker.setBounds           (x * 9,     0,          x * 2,      y);
    deckAnimation.setBounds         (x * 3,     y * 3,      x * 6,      y * 6);
    
    if(deck == Deck::Left)
    {
        speed.setBounds             (x,         y * 4,       x,         y * 5);
        volume.setBounds            (x * 10,    y * 4,       x,         y * 5);
        playPauseButton.setBounds   (x,         y * 10,      x * 1.5,   y * 1.5);
        cueButton.setBounds         (x * 3,     y * 10,      x * 1.5,   y * 1.5);
        currentTime.setBounds       (x * 5,     y * 10,      x * 1.5,   y * 1.5);

    }
    if(deck == Deck::Right)
    {
        speed.setBounds             (x * 10,    y * 4,       x,         y * 5);
        volume.setBounds            (x,         y * 4,       x,         y * 5);
        currentTime.setBounds       (x * 5.5f,  y * 10,      x * 1.5,   y * 1.5);
        cueButton.setBounds         (x * 7.5f,  y * 10,      x * 1.5,   y * 1.5);
        playPauseButton.setBounds   (x * 9.5f,  y * 10,      x * 1.5,   y * 1.5);
    }
}

//==============================================================================

/** Process user click
 @param button juce::Button*/
void DeckGUI::buttonClicked(Button* button)
{
    // playPause button Logic
    if(button == &playPauseButton)
    {
        if (player->isPlaying())
            player->stop();
        else
        {
            player->start();
        }
        cueCounter = 0;
    }
    // cue button Logic
    if (button == &cueButton)
    {
        if(player->isPlaying())
        {
            player->stop();
            player->setPosition(cue);
            cueCounter += 1;
        }
        else
        {
            cue = player->getPosition();
            player->setPosition(cue);
            cueCounter += 1;
            if(cueCounter ==2)
            {
                cue = 0;
                player->setPosition(cue);
                cueCounter = 0;
            }
            player->stop();
            updateTimeTracker();
        }
        
    }
    // load button logic
    if (button == &loadButton)  // open the file chooser
    {
        // get flag integer
        int fileChooserFlags = FileBrowserComponent::canSelectFiles;
        
        // launch file browser window async
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            // get chosen file
            File file = chooser.getResult();
            // load audio file
            player->loadURL(URL{file});
            // load waveform display
            loadWaveform(URL{file});
            // update current time
            updateTimeTracker();
        });
    }
}

bool DeckGUI::isInterestedInFileDrag (const juce::StringArray &files)
{
    std::cout<< "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    if (files.size() ==1)
    {
        File file = files[0];
        
        player->loadURL(URL{file});
        loadWaveform(URL{file});
        updateTimeTracker();
    }
}

void DeckGUI::timerCallback()
{
    // Set position of the waveform line component
    waveformDisplay.setPlayheadPosition(player->getPositionRelative());
    // Set position of the time tracker component
    timeTracker.setCurrentTime(player->getPosition());
    // Set track length of the time tracker component
    timeTracker.setRemainingTime(player->getTrackLength());
}

bool DeckGUI::isInterestedInDragSource (const SourceDetails &dragSourceDetails)
{
    return true;
}

void  DeckGUI::itemDropped (const SourceDetails &dragSourceDetails)
{
    cout<<"DeckGUI::itemDropped"<<endl;
    
    File file = String(dragSourceDetails.description);
    
    player->loadURL(URL{file});
    loadWaveform(URL{file});
    updateTimeTracker();
}
void DeckGUI::loadWaveform(URL file)
{
    waveformDisplay.loadURL(file);
}

void DeckGUI::updateTimeTracker()
{
    timeTracker.setCurrentTimeToZero();
}

