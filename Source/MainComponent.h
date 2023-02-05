#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "Playlist.h"
#include "Crossfader.h"

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
    
    // Required for Waveform Display
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};

    // Controller
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};

    // View
    DeckGUI deckGUI1{&player1, &crossfader, formatManager, thumbCache, false};
    DeckGUI deckGUI2{&player2, &crossfader, formatManager, thumbCache, true};
    
    Crossfader crossfader{&player1, &player2};
    
    MixerAudioSource mixerSource;
    
    Playlist playlist;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
