/*
  ==============================================================================

    WaveformDisplay.h
    Created: 12 Jan 2023 11:22:30pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

using namespace juce;
using namespace std;

class WaveformDisplay  : public Component,
                         public ChangeListener

{
public:
    WaveformDisplay(AudioFormatManager & formatManagerToUse,
                    AudioThumbnailCache & cacheToUse,
                    DJAudioPlayer* _player);
    ~WaveformDisplay() override;
    
//==============================================================================

    void paint (Graphics&) override;
    void resized() override;
    
//==============================================================================

    /**Listens for changes in the thumbnail to redraw**/
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    /**Load waveform thumbnail**/
    void loadURL(juce::URL audioURL);
    
    /**set the relative position of the playhead**/
    void setPositionRelative(double pos);
    
    /**Updates position of track when user click in the waveform component**/
    void mouseDown (const MouseEvent &event) override;

private:
    
    bool fileLoaded;
    double position;
    AudioThumbnail audioThumb;
    DJAudioPlayer* player;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
