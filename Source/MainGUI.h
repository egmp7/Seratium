/*
  ==============================================================================

    MainGUI.h
    Created: 5 Feb 2023 10:44:19am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "Crossfader.h"
#include "Playlist.h"

using namespace juce;

//==============================================================================

class MainGUI  : public Component
{
public:
    MainGUI(DJAudioPlayer* _player1,
            DJAudioPlayer* _player2,
            AudioFormatManager & _formatManagerToUse,
            AudioThumbnailCache & _thumbCacheToUse);
    ~MainGUI() override;

    void paint (Graphics&) override;
    void resized() override;

private:
    
    // Components
    DeckGUI deckGUI1;
    DeckGUI deckGUI2;
    Crossfader crossfader;
    Playlist playlist;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainGUI)
};
