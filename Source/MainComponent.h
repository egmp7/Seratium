#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "Playlist.h"
#include "Crossfader.h"
#include "MainGUI.h"

//==============================================================================

class MainComponent  : public juce::AudioAppComponent
{                       
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    
    // Required for Waveform Display instantiation
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};

    // Controllers
    MixerAudioSource mixerSource;
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};
    
    // Views
    MainGUI mainGUI{&player1, &player2, formatManager, thumbCache};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
