/*
  ==============================================================================

    TimeTracker.h
    Created: 5 Feb 2023 12:01:09pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Format.h"

using namespace juce;

//==============================================================================
/*
*/
class TimeTracker  : public Component
{
public:
    TimeTracker();
    ~TimeTracker() override;

    void paint (juce::Graphics&) override;
    void resized() override;
        
    /**set the current value of the track position in seconds**/
    void setCurrentTime(float time);
    
    /**set the remaining value of the track length in seconds*/
    void setRemainingTime(float trackLength);
    
    float currentTime;

private:
    
    float remainingTime;
        
    Rectangle<float> currentTimeRect;
    Rectangle<float> remainingTimeRect;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeTracker)
};
