/*
  ==============================================================================

    Volume.h
    Created: 11 Feb 2023 12:21:51am
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
class Volume  :

public Component,
public Slider::Listener

{
public:
    Volume();
    ~Volume() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    /**Sets the value of the volumeSlider
     @param slider pointer from Slider::Listener**/
    void sliderValueChanged(Slider* slider) override;
    /**Gets the value of the volumeSlider
     @returns float between 0.0f and 1.0f**/
    float getValue();

private:
    
    Slider volumeSlider;
    Fader volumeCustomFader;
    FLookAndFeel volumeLookAndFeel{ImageFileFormat::loadFrom(File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/volFader.png"))};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Volume)
};
