/*
  ==============================================================================

    PlayPauseButton.h
    Created: 13 Feb 2023 2:53:42am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CueButton.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class PlayPauseButton  :

public Component,
public Button::Listener

{
public:
    PlayPauseButton(DJAudioPlayer*,
                    CueButton*);
    ~PlayPauseButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    /**Implementation for  Button when clicked
     @param button button clicked */
    void buttonClicked(Button *) override;

private:
    
    ImageButton playPauseButton{"PlayPause"};
    DJAudioPlayer* player;
    CueButton* cueButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayPauseButton)
};
