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
#include "TimeTracker.h"
#include "DeckAnimation.h"
#include "Crossfader.h"

using namespace juce;
using namespace std;

//==============================================================================

class DeckGUI  : public Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer,
                 public DragAndDropTarget
{
public:
    DeckGUI(DJAudioPlayer* player,
            Crossfader* _crossfader,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse,
            bool _mirror);
    ~DeckGUI() override;

    
    void paint (juce::Graphics&) override;
    void resized() override;
    
//==============================================================================
    
    /**Implement Button::Listener*/
    void buttonClicked(Button *) override;
    /**Implement Slider::Listener*/
    void sliderValueChanged (Slider *slider) override;
    /**Checks drag and drop  system files*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Loads system audio files to the application*/
    void filesDropped (const StringArray &files, int x, int y) override;
    /**Checks for drag and drop object sources*/
    bool isInterestedInDragSource (const SourceDetails &dragSourceDetails) override;
    /**Loads audio files to the application**/
    void  itemDropped (const SourceDetails &dragSourceDetails) override;
    /**Callback function that runs in a separate threath**/
    void timerCallback() override;
    /**Helper to redraw audio thumbnails*/
    void loadWaveform(File file);

private:
    
    // Controllers
    DJAudioPlayer* player;
    Crossfader* crossfader;
        
    // GUI Components
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    WaveformDisplay waveformDisplay;
    TimeTracker timeTracker;
    DeckAnimation deckAnimation {player};
    
    //Utilities
    FileChooser fChooser{"Select a file..."};
    bool mirror;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
