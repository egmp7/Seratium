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

    void paint (Graphics&) override;
    void resized() override;
        
    /**sets the current value of the track position in seconds
     @param time current time of players*/
    void setCurrentTime(float time);
    
    /**sets the remaining value of the track length in seconds
     @param trackLength remaining time is equal to the difference of total length minus current time*/
    void setRemainingTime(float trackLength);
    
    /**sets the current time to zero**/
    void setCurrentTimeToZero();
    
private:
    
    float currentTime;
    float remainingTime;
        
    Rectangle<float> currentTimeRect;
    Rectangle<float> remainingTimeRect;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeTracker)
};
