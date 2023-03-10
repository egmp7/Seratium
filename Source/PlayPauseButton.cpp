/*
  ==============================================================================

    PlayPauseButton.cpp
    Created: 13 Feb 2023 2:53:42am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayPauseButton.h"

//==============================================================================
PlayPauseButton::PlayPauseButton(DJAudioPlayer* _player,
                                 CueButton* _cueButton)
:
player(_player),
cueButton(_cueButton)
{
    addAndMakeVisible(playPauseButton);
    playPauseButton.addListener(this);
    playPauseButton.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                BinaryData::playPause_png,BinaryData::playPause_pngSize),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);
}

PlayPauseButton::~PlayPauseButton()
{
}

void PlayPauseButton::paint (juce::Graphics& g)
{
}

void PlayPauseButton::resized()
{
    playPauseButton.setBounds(getLocalBounds());
}

/** Process user click
 @param button juce::Button*/
void PlayPauseButton::buttonClicked(Button* button)
{

    if (player->isPlaying())
        player->stop();
    else
        player->start();
    cueButton->resetCueCounter();
}
