/*
  ==============================================================================

    currentTime.h
    Created: 12 Feb 2023 8:03:12pm
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
class CurrentTime  : public Component
{
public:
    CurrentTime();
    ~CurrentTime() override;

    void paint (Graphics&) override;
    void resized() override;
    /**Sets the time from the Timer threath in DeskGUI
     @param _time in seconds**/
    void setTime(float _time);

private:
    
    float time;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurrentTime)
};
