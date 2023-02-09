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

    /**Listens for changes in the thumbnail to redraw
     @param source not used*/
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    /**Load waveform thumbnail
     @param audioURL file to be loaded*/
    void loadURL(URL audioURL);
    
    /**Updates position of the playhead when user clicks this component
     @param event gets the distance between the click and the start of the component */
    void mouseDown (const MouseEvent &event) override;
    
    /**set the relative position of the playhead
     @param pos current position of the player in seconds*/
    void setPlayheadPosition(double pos);

private:
    

    
    bool fileLoaded;
    double playheadPosition;
    AudioThumbnail audioThumb;
    DJAudioPlayer* player;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
