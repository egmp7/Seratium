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
waveformDisplay(formatManagerToUse, cacheToUse, _player, &cueButton),
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


    // components
    addAndMakeVisible(trackName);
    addAndMakeVisible(volume);
    addAndMakeVisible(cueButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(speed);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(deckAnimation);
    addAndMakeVisible(currentTime);
    addAndMakeVisible(remainingTime);
    
    // ids
    if(deck == Deck::Left)
        volume.setComponentID("volLeft");
    if(deck == Deck::Right)
        volume.setComponentID("volRight");

    // Timer class
    startTimer(50);
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
    g.fillRect (fileNameRectangle);
    g.setColour (juce::Colours::white);
    g.drawText(fileName, fileNameRectangle, Justification::centredLeft);
    
}

void DeckGUI::resized()
{
    double x = getWidth() / 12;
    double y = getHeight() / 12;
    
    // GUI Components               x           y           width       height
    loadButton.setBounds            (x,         0,          x,          y);
    trackName.setBounds             (x * 2,     0,          x * 7,      y);
    remainingTime.setBounds         (x * 9,     0,          x * 2,      y);
    waveformDisplay.setBounds       (x,         y,          x * 10,     y * 2);
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
        cueButton.resetCueCounter();
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
        waveformDisplay.loadURL(URL{file});
        trackName.setFileName(file.getFileName());
    }
}

void DeckGUI::timerCallback()
{
    // Set position of the waveform line component
    waveformDisplay.setPlayheadPosition(player->getPositionRelative());
    // Set current time of player in seconds
    currentTime.setTime(player->getPosition());
    // Set current time in remaining time
    remainingTime.setTime(player->getPosition());
    // Set Tracklength in remaining time
    remainingTime.setTrackLength(player->getTrackLength());
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
    waveformDisplay.loadURL(URL{file});
    trackName.setFileName(file.getFileName());

}
