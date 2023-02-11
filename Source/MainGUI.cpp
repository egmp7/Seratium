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
playlist(_formatManagerToUse)
{
    addAndMakeVisible(deckGUI1);
    deckGUI1.setComponentID("deckGUI1");

    addAndMakeVisible(deckGUI2);
    deckGUI2.setComponentID("deckGUI2");
    
    addAndMakeVisible(crossfader);
    addAndMakeVisible(playlist);
    
    crossfaderPNG = ImageFileFormat::loadFrom(File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/crossfader.png"));
    volPNG =
        ImageFileFormat::loadFrom(File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/volFader.png"));
    speedPNG =
        ImageFileFormat::loadFrom(File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/speedFader.png"));
    
    setFramesPerSecond (60);
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

void MainGUI::paintOverChildren(Graphics & g)
{
    g.drawImage(crossfaderPNG,crossfaderThumUpdate,RectanglePlacement());
    g.drawImage(volPNG,volFaderThumUpdate1,RectanglePlacement());
    g.drawImage(volPNG,volFaderThumUpdate2,RectanglePlacement());
    g.drawImage(speedPNG,speedFaderThumUpdate1,RectanglePlacement());
    g.drawImage(speedPNG,speedFaderThumUpdate2,RectanglePlacement());




}

void MainGUI::update()
{
    crossfaderThumUpdate = RectanglesUtility::catchHorizontalThumRectangle(
        crossfader.getX(),
        crossfader.getY(),
        crossfader.getWidth(),
        crossfader.getHeight(),
        crossfader.thumPosition() + crossfader.getX());
    
    SliderModel volumeSliderModel1 = deckGUI1.getVolSliderModel();
    
    volFaderThumUpdate1 = RectanglesUtility::catchVerticalThumRectangle(
       volumeSliderModel1.x,
       volumeSliderModel1.y,
       volumeSliderModel1.width,
       volumeSliderModel1.height,
       volumeSliderModel1.value);
    
    SliderModel volumeSliderModel2 = deckGUI2.getVolSliderModel();
    
    volFaderThumUpdate2 = RectanglesUtility::catchVerticalThumRectangle(
       volumeSliderModel2.x + getWidth()/2,
       volumeSliderModel2.y,
       volumeSliderModel2.width,
       volumeSliderModel2.height,
       volumeSliderModel2.value);
    
    SliderModel speedSliderModel1 = deckGUI1.getSpeedSliderModel();
    
    speedFaderThumUpdate1 = RectanglesUtility::catchVerticalThumRectangle(
       speedSliderModel1.x,
       speedSliderModel1.y,
       speedSliderModel1.width,
       speedSliderModel1.height,
       speedSliderModel1.value);
    
    SliderModel speedSliderModel2 = deckGUI2.getSpeedSliderModel();
    
    speedFaderThumUpdate2 = RectanglesUtility::catchVerticalThumRectangle(
       speedSliderModel2.x + getWidth()/2,
       speedSliderModel2.y,
       speedSliderModel2.width,
       speedSliderModel2.height,
       speedSliderModel2.value);
}
