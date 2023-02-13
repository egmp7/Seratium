/*
  ==============================================================================

    currentTime.h
    Created: 12 Feb 2023 8:03:12pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
*/
class CurrentTime  : public juce::Component
{
public:
    CurrentTime();
    ~CurrentTime() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurrentTime)
};
