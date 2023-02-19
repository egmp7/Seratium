/*
  ==============================================================================

    Crossfader.h
    Created: 4 Feb 2023 10:41:54pm
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
 
 The crossfader component sets the gain value between 0 and 1 for playerA and playerB
 Also, the state changes when user interacts with volume sliders
 
 NEEDS TO CONNECT TO VOLUME COMPONENT
 
*/
class Crossfader  : public Component,
                    public Slider::Listener
{
public:
    Crossfader(DJAudioPlayer* _player1, DJAudioPlayer* _player2);
    ~Crossfader() override;

    void paint (Graphics&) override;
    void resized() override;
    
    /**crossfader listener
     @param *slider crossfader moved*/
    void sliderValueChanged (Slider *slider) override;
    /**set fader value
     @param gain value for the faders
     @param deckID id to recognize which fader needs to be set*/
    /**Sets VolumeL value
     @param value between 0.0f and 1.0f**/
    void setVolumeL(float value);
    /**Sets VolumeR value
     @param value between 0.0f and 1.0f**/
    void setVolumeR(float value);
    
private:
    
    /**algorithm to get main gain value**/
    void mixVolumesAlgorithm();
    
    Slider crossfaderSlider;
    FaderLookAndFeel crossfaderLookAndFeel
        {ImageFileFormat::loadFrom(
           BinaryData::crossfader_png,BinaryData::crossfader_pngSize),
        FaderStyle::MidGrow
        };
        
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    
    float volumeL;
    float volumeR;
    float mainVolumeL;
    float mainVolumeR;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Crossfader)
};
