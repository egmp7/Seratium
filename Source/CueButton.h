/*
  ==============================================================================

    CueButton.h
    Created: 13 Feb 2023 12:46:26am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class CueButton  :

public Component,
public Button::Listener

{
public:
    CueButton(DJAudioPlayer*);
    ~CueButton() override;

    void paint (Graphics&) override;
    void resized() override;
    
    /**Implementation for  cue button when clicked
     @param button button clicked */
    void buttonClicked(Button *) override;
    /**resets the cueCounter to 0**/
    void resetCueCounter();
    /**gets the position of the cue in seconds**/
    int getCuePosition();

private:
    
    DJAudioPlayer* player;
    int cueCounter;
    int cuePosition;
    ImageButton cue{"CUE"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CueButton)
};
