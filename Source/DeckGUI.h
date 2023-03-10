/*
  ==============================================================================

    DeckGUI.h
    Created: 12 Jan 2023 7:05:21pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// controllers
#include "Crossfader.h"
#include "DJAudioPlayer.h"
// child components
#include "WaveformDisplay.h"
#include "DeckAnimation.h"
#include "Volume.h"
#include "Speed.h"
#include "CurrentTime.h"
#include "RemainingTime.h"
#include "PlayPauseButton.h"
#include "CueButton.h"
#include "LoadButton.h"
#include "TrackName.h"

using namespace juce;
using namespace std;

//==============================================================================

enum class Deck{Left,Right};

class DeckGUI  :

public Component,
public FileDragAndDropTarget,
public DragAndDropTarget,
public Timer

{
public:
    DeckGUI(DJAudioPlayer* player,
            Crossfader* _crossfader,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse,
            Deck);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
//==============================================================================
    
    /**Checks drag and drop  system files when entering the component rectangle
     @param &files an array of files  selected when dragging
     @returns true when item is inside the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Loads system audio files to the application
     @param &files an array of files  selected when dragging
     @param x coordenate relative to the component,
     @param y coordenate relative to the component*/
    void filesDropped (const StringArray &files, int x, int y) override;
    /**Checks for drag and drop object sources
     @param &dragSourceDetails contains file names
     @returns true when item is inside the component */
    bool isInterestedInDragSource (const SourceDetails &dragSourceDetails) override;
    /**Loads audio files to the application
     @param &dragSourceDetails contains file names*/
    void itemDropped (const SourceDetails &dragSourceDetails) override;
    /**Updates time tracke with a setterr**/
    void timerCallback() override;

private:
    
    // Controllers
    DJAudioPlayer* player;
    Crossfader* crossfader;
        
    // GUI Components
    PlayPauseButton playPauseButton{player, &cueButton};
    LoadButton loadButton {player, &waveformDisplay, &trackName};
    WaveformDisplay waveformDisplay;
    Volume volume;
    Speed speed;
    DeckAnimation deckAnimation;
    CurrentTime currentTime;
    RemainingTime remainingTime;
    CueButton cueButton {player};
    TrackName trackName;
    
    //Utilities
    Deck deck;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
