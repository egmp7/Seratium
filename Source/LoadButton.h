/*
  ==============================================================================

    LoadButton.h
    Created: 13 Feb 2023 1:55:48am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "TrackName.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class LoadButton  :

public Component,
public Button::Listener

{
public:
    LoadButton(DJAudioPlayer*,
               WaveformDisplay*,
               TrackName*);
    ~LoadButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**Implementation for  LoadButton when clicked
     @param button button clicked */
    void buttonClicked(Button *) override;
    
private:
    DJAudioPlayer* player;
    WaveformDisplay* waveform;
    TrackName*  trackName;
    FileChooser fChooser{"Select a file..."};
    ImageButton loadButton{"LOAD"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadButton)
};
