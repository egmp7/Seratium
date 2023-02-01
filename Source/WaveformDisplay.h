/*
  ==============================================================================

    WaveformDisplay.h
    Created: 12 Jan 2023 11:22:30pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                    juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    
    void changeListenerCallback (juce::ChangeBroadcaster *source) override;
    
    void resized() override;
    
    void loadURL(juce::URL audioURL);
    
    /**set the relative position of the playhead**/
    void setPositionRelative(double pos);

private:
    
    bool fileLoaded;
    double position;
    juce::AudioThumbnail audioThumb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
