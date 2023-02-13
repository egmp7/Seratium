/*
  ==============================================================================

    MainGUI.cpp
    Created: 5 Feb 2023 10:44:19am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "MainGUI.h"

//==============================================================================
MainGUI::MainGUI(DJAudioPlayer* _player1,
                 DJAudioPlayer* _player2,
                 AudioFormatManager & _formatManagerToUse,
                 AudioThumbnailCache & _thumbCacheToUse)
:
deckGUI1(_player1, &crossfader, _formatManagerToUse, _thumbCacheToUse, Deck::Left),
deckGUI2(_player2, &crossfader, _formatManagerToUse, _thumbCacheToUse, Deck::Right),
crossfader(_player1, _player2),
playlist(_formatManagerToUse)
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

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
        
}

void MainGUI::resized()
{
    float x = getWidth()/24;
    float y = getHeight()/16;
    

    deckGUI1.setBounds  (0,
                         0,
                         x * 12,
                         y * 12);
    
    deckGUI2.setBounds  (x * 12,
                         0,
                         x * 12,
                         y * 12);
    
    crossfader.setBounds(x * 8,
                         y * 10,
                         x * 8,
                         y);
    playlist.setBounds(0,
                       y * 12,
                       x * 24,
                       y * 4);
}
