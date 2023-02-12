/*
  ==============================================================================

    Speed.h
    Created: 11 Feb 2023 1:05:25am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Fader.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class Speed
:

public Component,
public Slider::Listener

{
public:
    Speed();
    ~Speed() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**Sets the value of the speedSlider
     @param slider pointer from Slider::Listener**/
    void sliderValueChanged(Slider* slider) override;
    /**Gets the value of the speedSlider
     @returns float between 0.0f and 1.0f**/
    float getValue();

private:
    
    Slider speedSlider;
    //FLookAndFeel speedLookAndFeel{FaderOrientation::v};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Speed)
};
