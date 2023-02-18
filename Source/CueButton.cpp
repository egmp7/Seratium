/*
  ==============================================================================

    CueButton.cpp
    Created: 13 Feb 2023 12:46:26am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CueButton.h"

//==============================================================================
CueButton::CueButton(DJAudioPlayer* _player)
:
player(_player)
{
    addAndMakeVisible(cue);
    cue.addListener(this);
    cue.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                File("/Users/erickgonzalez/Documents/Programs/Seratium/Assets/cue.png")),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);

}

CueButton::~CueButton()
{
}

void CueButton::paint (juce::Graphics& g)
{
}

void CueButton::resized()
{
    cue.setBounds(getLocalBounds());
}

void CueButton::buttonClicked(Button *)
{
    if (cueCounter == 1) // set player to start position
    {
        player->setPosition(0.0f);
        cuePosition =0.0f;
        resetCueCounter();
    }
    else
    {
        if (player->isPlaying()) // set player to last cue
        {
            player->stop();
            player->setPosition(cuePosition);
        }
        else // save new cue
        {
            cuePosition = player->getPosition();
        }
        ++cueCounter;
    }
}

void CueButton::resetCueCounter()
{
    cueCounter = 0;
}

double CueButton::getCuePosition()
{
    return cuePosition;
}
