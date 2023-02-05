/*
  ==============================================================================

    TimeTracker.h
    Created: 5 Feb 2023 12:01:09pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    void setCurrentTime(int time);
    
    /**set the remaining value of the track length in seconds*/
    void setRemainingTime(int trackLength);

private:
    
    Rectangle<float> currentTimeRect;
    Rectangle<float> remainingTimeRect;
    int currentTime;
    int remainingTime;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeTracker)
};
