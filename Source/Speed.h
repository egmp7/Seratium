/*
  ==============================================================================

    Speed.h
    Created: 11 Feb 2023 1:05:25am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "FaderLookAndFeel.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
 // NEEDS CONNECTION TO PLAYER
*/
class Speed
:

public Component,
public Slider::Listener

{
public:
    // add player 
    Speed(DJAudioPlayer*);
    ~Speed() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**Sets the value of the speedSlider
     @param slider pointer from Slider::Listener**/
    void sliderValueChanged(Slider* slider) override;

private:
    
    Slider speedSlider;
    FaderLookAndFeel speedLookAndFeel
        {ImageFileFormat::loadFrom(
           File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/speedFader.png")),
        FaderStyle::MidGrow
        };
    DJAudioPlayer* player;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Speed)
};
