/*
  ==============================================================================

    remainingTime.h
    Created: 12 Feb 2023 8:04:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Format.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class RemainingTime  : public Component
{
public:
    RemainingTime();
    ~RemainingTime() override;

    void paint (Graphics&) override;
    void resized() override;
    
    /**Sets the current time from the Timer threath  in DeckGUi
     @param time in seconds**/
    void setTime(float _time);
    /**Sets the track length from the Timer threth in DeckGUI
     @param _trackLength in seconds**/
    void setTrackLength(float _time);

private:
    
    /**updates the remainingTime and repaints the Graphic object**/
    void update();
    
    float remainingTime;
    float time;
    float trackLength;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RemainingTime)
};
