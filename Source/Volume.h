/*
  ==============================================================================

    Volume.h
    Created: 11 Feb 2023 12:21:51am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Crossfader.h"
#include "FaderLookAndFeel.h"

using namespace juce;
using namespace std;


//==============================================================================
/*
 Volume components works along with the crossfader,
 its in charge of updating the Crossfader fader value between 0.0f and 1.0f
 
 // NEEDS CONNECTION TO CROSSFADER
*/
class Volume  :

public Component,
public Slider::Listener

{
    
public:
    
    Volume(Crossfader*);
    ~Volume() override;

    void paint (Graphics&) override;
    void resized() override;
    
    /**Sets the value of the crossfader volumes
     @param slider pointer from Slider::Listener**/
    void sliderValueChanged(Slider* slider) override;

private:
    
    Slider volumeSlider;
    FaderLookAndFeel volumeLookAndFeel
        {ImageFileFormat::loadFrom(
           File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/volFader.png")),
        FaderStyle::FullGrow
        };
    
    Crossfader* crossfader;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Volume)
};
