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
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(crossfader);
    addAndMakeVisible(playlist);
}

MainGUI::~MainGUI()
{

}

void MainGUI::paint (juce::Graphics& g)
{
    g.fillAll(Colour(36, 17, 51));
}

void MainGUI::paintOverChildren(Graphics & g)
{
    

    g.setColour (Colour(60,21,108));
    g.fillRect(deckDivision);
    g.fillRoundedRectangle(logo,10.0f);
    g.drawImage(ImageFileFormat::loadFrom(
                BinaryData::logo_png, BinaryData::logo_pngSize),
                logo,
                RectanglePlacement());
    
}

void MainGUI::resized()
{
    double x = getWidth() / 24;
    double y = getHeight() / 16;
    double py = y/4;
    

    deckGUI1.setBounds  (0,
                         0,
                         x * 12,
                         y * 11);
    
    deckGUI2.setBounds  (x * 12,
                         0,
                         x * 12,
                         y * 11);
    
    crossfader.setBounds(x * 8,
                         9*y + 2*py,
                         x * 8,
                         y);
    playlist.setBounds(0,
                       y * 11,
                       x * 24,
                       y * 5);
    logo.setBounds(11*x, 5*y+py, 2*x, 2*y);
    
    deckDivision.setBounds(12*x -3,
                           0,
                           6,
                           9*y + 2*py);
}
