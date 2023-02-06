/*
  ==============================================================================

    MainGUI.cpp
    Created: 5 Feb 2023 10:44:19am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainGUI.h"

//==============================================================================
MainGUI::MainGUI(DJAudioPlayer* _player1,
                 DJAudioPlayer* _player2,
                 AudioFormatManager & _formatManagerToUse,
                 AudioThumbnailCache & _thumbCacheToUse)
:
deckGUI1(_player1, &crossfader, _formatManagerToUse, _thumbCacheToUse, false),
deckGUI2(_player2, &crossfader, _formatManagerToUse, _thumbCacheToUse, true),
crossfader(_player1, _player2),
playlist(_player1, _player2, &deckGUI1, &deckGUI2, _formatManagerToUse)
{
    addAndMakeVisible(deckGUI1);
    deckGUI1.setComponentID("deckGUI1");

    addAndMakeVisible(deckGUI2);
    deckGUI2.setComponentID("deckGUI2");
    
    addAndMakeVisible(crossfader);
    addAndMakeVisible(playlist);
}

MainGUI::~MainGUI()
{

}

void MainGUI::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void MainGUI::resized()
{
    int decksWidth = getWidth();
    int decksHeight = getHeight() * 3 / 4;

    deckGUI1.setBounds  (0,
                         0,
                         decksWidth / 2,
                         decksHeight);
    
    deckGUI2.setBounds  (decksWidth / 2,
                         0,
                         decksWidth / 2,
                         decksHeight);
    
    crossfader.setBounds(decksWidth / 4,
                         decksHeight - decksHeight / 7,
                         decksWidth / 2,
                         decksHeight / 7);
    playlist.setBounds(0,
                       decksHeight,
                       getWidth(),
                       getHeight() / 4);
}
