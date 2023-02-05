/*
  ==============================================================================

    DeckGUI.h
    Created: 12 Jan 2023 7:05:21pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "DeckAnimation.h"
#include "Crossfader.h"

using namespace juce;
using namespace std;

//==============================================================================

class DeckGUI  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            Crossfader* _crossfader,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse,
            bool _mirror);
    ~DeckGUI() override;

//==============================================================================
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
//==============================================================================
    
    // Buttons and Sliders
    
    /** implement Button::Listener*/
    void buttonClicked(Button *) override;
    /** implement Slider::Listener*/
    void sliderValueChanged (Slider *slider) override;
    
//==============================================================================
    
    // Drag and Drop
    
    /**Checks when user hover the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Runs when the user release the click*/
    void filesDropped (const StringArray &files, int x, int y) override;
    
//==============================================================================

    /**Callback function that runs in a different threath**/
    void timerCallback() override;

private:
    
    // Mirror GUI
    bool mirror;
    
    // GUI Components
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    WaveformDisplay waveformDisplay;
    DeckAnimation deckAnimation;
    
    // Tracking time components
    Rectangle<float> currentTrackTimeComp;
    Rectangle<float> remainingTrackTimeComp;
    int currentTrackTime;
    int remainingTrackTime;
    void setCurrentTrackTime(int time);
    void setRemainingTrackTime(int trackLength);
    
    // Controllers
    DJAudioPlayer* player;
    Crossfader* crossfader;
    
    //Utilities
    FileChooser fChooser{"Select a file... Mijo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
