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

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Buttons and Sliders implementation
    
    /** implement Button::Listener*/
    void buttonClicked(juce::Button *) override;
    /** implement Slider::Listener*/
    void sliderValueChanged (juce::Slider *slider) override;
    
    // Drag and Drop
    
    bool isInterestedInFileDrag (const juce::StringArray &files) override;
    
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    void timerCallback() override;


private:
    
    //Buttons
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    //Sliders
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    
    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;
    
    //Utilities
    juce::FileChooser fChooser{"Select a file..."};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
