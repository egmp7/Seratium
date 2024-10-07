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
    
    // components
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(cueButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(trackName);
    addAndMakeVisible(volume);
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
}

void DeckGUI::resized()
{
    double x = getWidth() / 12;
    double px = x/4;
    double y = getHeight() / 11;
    double py = y/4;
    
    // GUI Components               x           y           width       height
    loadButton.setBounds            (x,         py,         x,          y);
    trackName.setBounds             (2*x +px,   py,         7*x -px,    y);
    remainingTime.setBounds         (9*x + px,  py,         2*x -px,    y);
    waveformDisplay.setBounds       (x,         y + py*2,   x * 10,     y * 2);
    deckAnimation.setBounds         (3*x + 2*px,3*y + 3*py, x * 5,      y * 5);
    
    if(deck == Deck::Left)
    {
        speed.setBounds             (x + 2*px,  3*y + 3*py,  x,         y * 5);
        volume.setBounds            (9*x + 2*px,3*y + 3*py,  x,         y * 5);
        playPauseButton.setBounds   (x,         9*y +py,     x * 1.5,   y * 1.5);
        cueButton.setBounds         (x * 3,     9*y +py,     x * 1.5,   y * 1.5);
        currentTime.setBounds       (x * 5,     9*y +py,     x * 1.5,   y * 1.5);

    }
    if(deck == Deck::Right)
    {
        speed.setBounds             (9*x + 2*px,3*y + 3*py,  x,         y * 5);
        volume.setBounds            (x + 2*px,  3*y + 3*py,  x,         y * 5);
        currentTime.setBounds       (x * 5.5f,  9*y +py,     x * 1.5,   y * 1.5);
        cueButton.setBounds         (x * 7.5f,  9*y +py,     x * 1.5,   y * 1.5);
        playPauseButton.setBounds   (x * 9.5f,  9*y +py,     x * 1.5,   y * 1.5);
    }
}

//==============================================================================


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

bool DeckGUI::isInterestedInDragSource (const SourceDetails &dragSourceDetails)
{
    return true;
}

void DeckGUI::itemDropped(const SourceDetails& dragSourceDetails)
{
    cout << "DeckGUI::itemDropped" << endl;

    // Convert var to String safely using toString()
    juce::String filePath = dragSourceDetails.description.toString();

    // Create File object using the file path
    juce::File file(filePath);

    // Load the URL into the player and waveform display
    player->loadURL(juce::URL{ file });
    waveformDisplay.loadURL(juce::URL{ file });

    // Set track name using the file name
    trackName.setFileName(file.getFileName());
}

void DeckGUI::timerCallback()
{
    // Set position of the waveform line component
    waveformDisplay.setPlayheadPosition(player->getPositionRelative());
    // Set relative position of the waveform cue
    waveformDisplay.setCuePosition(cueButton.getCuePosition() / player->getTrackLength());
    // Set current time of player in seconds
    currentTime.setTime(player->getPosition());
    // Set current time in remaining time
    remainingTime.setTime(player->getPosition());
    // Set Tracklength in remaining time
    remainingTime.setTrackLength(player->getTrackLength());
}
