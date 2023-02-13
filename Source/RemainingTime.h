/*
  ==============================================================================

    remainingTime.h
    Created: 12 Feb 2023 8:04:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RemainingTime  : public juce::Component
{
public:
    RemainingTime();
    ~RemainingTime() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RemainingTime)
};
