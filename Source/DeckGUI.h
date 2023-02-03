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

using namespace juce;
using namespace std;

//==============================================================================

class DeckGUI  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse);
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

    void timerCallback() override;


private:
    
    // GUI Components
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    WaveformDisplay waveformDisplay;
    
    // Labels
    Label volLabel;
    
    DJAudioPlayer* player;
    
    //Utilities
    FileChooser fChooser{"Select a file... Mijo"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
