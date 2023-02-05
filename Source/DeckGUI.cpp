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
                 bool _mirror)
:
mirror(_mirror),
waveformDisplay(formatManagerToUse, cacheToUse, _player),
currentTrackTime(0),
remainingTrackTime(0),
player(_player),
crossfader(_crossfader)
{
    // play button
    addAndMakeVisible(playButton);
    playButton.addListener(this);

    // stop button
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);

    // load button
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    // vol slider
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    volSlider.setValue(1);

    // speed slider
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    speedSlider.setRange(0.5, 1.5);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    speedSlider.setValue(1);

    // other components
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(deckAnimation);

    startTimer(20);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}
void DeckGUI::paint (juce::Graphics& g)
{

    // background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
    g.setColour(Colours::white);
    g.drawText(String(currentTrackTime) + "s", currentTrackTimeComp, Justification::centred);
    g.drawText(String(remainingTrackTime) + "s", remainingTrackTimeComp, Justification::centred);

}

void DeckGUI::resized()
{
    
    double rowH = getHeight() / 7;
    double columnW = getWidth() / 8;
    
    // GUI Components               x          y           width       height
    loadButton.setBounds            (0,         0,          columnW,    rowH);
    waveformDisplay.setBounds       (columnW,   0,          columnW*6,  rowH);
    currentTrackTimeComp.setBounds  (columnW*7, 0,          columnW,    rowH/2);
    remainingTrackTimeComp.setBounds(columnW*7, rowH/2,     columnW,    rowH/2);
    
    if(!mirror)
    {
        speedSlider.setBounds           (0,         rowH,       columnW*2,  rowH*5);
        deckAnimation.setBounds         (columnW*2, rowH,       columnW*4,  rowH*5);
        volSlider.setBounds             (columnW*6, rowH,       columnW*2,  rowH*5);
        playButton.setBounds            (0,         rowH*6,     columnW*2,  rowH);
        stopButton.setBounds            (columnW*2, rowH*6,     columnW*2,  rowH);
    }
    else
    {
        speedSlider.setBounds           (columnW*6, rowH,       columnW*2,  rowH*5);
        deckAnimation.setBounds         (columnW*2, rowH,       columnW*4,  rowH*5);
        volSlider.setBounds             (0,         rowH,       columnW*2,  rowH*5);
        playButton.setBounds            (columnW*6, rowH*6,     columnW*2,  rowH);
        stopButton.setBounds            (columnW*4, rowH*6,     columnW*2,  rowH);
    }
}

//==============================================================================

/** Process user click
 @param button juce::Button*/
void DeckGUI::buttonClicked(juce::Button* button)
{
    if(button == &playButton)
    {
        player->start();
    }
    if (button == &stopButton)
    {
        player->stop();
    }
    if (button == &loadButton)  // open the file chooser
    {
        // get flag integer
        int fileChooserFlags = FileBrowserComponent::canSelectFiles;
        
        // launch file browser window async
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            // get chosen file
            juce::File chosenFile = chooser.getResult();
            // load audio file
            player->loadURL(juce::URL{chosenFile});
            // load waveform display
            waveformDisplay.loadURL(juce::URL{chosenFile});
        });
    }
}
/** Process user silder action
 @param button juce::Button*/
void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        crossfader->setFaderGain(slider->getValue(), getComponentID());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
}
bool DeckGUI::isInterestedInFileDrag (const juce::StringArray &files)
{
    std::cout<< "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}
void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    std::cout<< "DeckGUI::filesDropped" << std::endl;
    
    if (files.size() ==1)
    {
        player->loadURL(URL{File{files[0]}});
        waveformDisplay.loadURL(URL{File{files[0]}});
        
    }

}
void DeckGUI::setCurrentTrackTime(int time)
{
    if(currentTrackTime != time && time != 0.0f)
    {
        currentTrackTime = time;
        repaint();
    }
        
}
void DeckGUI::setRemainingTrackTime(int trackLength)
{
    if(trackLength != 0)
    {
        remainingTrackTime = trackLength - currentTrackTime;
       // repaint();
    }
    
}
void DeckGUI::timerCallback()
{
    // Set position of the waveform line
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    // Set position of the deck animation
    deckAnimation.setPosition(player->getPosition());
    // Set position of Timer Track Components
    setCurrentTrackTime(player->getPosition());
    setRemainingTrackTime(player->getTrackLength());
}

