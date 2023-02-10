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
#include "FadersLookAndFeel.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
 
 The crossfader component sets the gain value between 0 and 1 for playerA and playerB
 Also, the state changes when user interacts with volume sliders
 
*/
class Crossfader  : public Component,
                    public Slider::Listener
{
public:
    Crossfader(DJAudioPlayer* _player1, DJAudioPlayer* _player2);
    ~Crossfader() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**crossfader listener
     @param *slider crossfader moved*/
    void sliderValueChanged (Slider *slider) override;
    /**returns the position of the thum in pixels from the edge of this component
     @returns position in pixels*/
    float thumPosition();
    /**set fader value
     @param gain value for the faders
     @param deckID id to recognize which fader needs to be set*/
    void setFaderGain(float gain, String deckID);
    
private:
    
    /**algorithm to get main gain value**/
    void mainGainAlgorithm();
    
    Slider crossfaderSlider;
    
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    
    float faderA;
    float faderB;
    float mainGainA;
    float mainGainB;
    
    FadersLookAndFeel crossfaderLookAndFeel{FaderType::horizontal};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Crossfader)
};
