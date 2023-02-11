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
#include "RectanglesUtility.h"
#include "SliderModel.h"

using namespace juce;

//==============================================================================

class MainGUI  : public AnimatedAppComponent
{
public:
    MainGUI(DJAudioPlayer* _player1,
            DJAudioPlayer* _player2,
            AudioFormatManager & _formatManagerToUse,
            AudioThumbnailCache & _thumbCacheToUse);
    ~MainGUI() override;

    void paint (Graphics&) override;
    void resized() override;
    
    /**Updates the thum position of the sliders**/
    void update() override;
    /**Paint objects over components
     @param g paints the thum images of sliders**/
    void paintOverChildren(Graphics&) override;

private:
    
    // Components
    DeckGUI deckGUI1;
    DeckGUI deckGUI2;
    Crossfader crossfader;
    Playlist playlist;
    
    Image crossfaderPNG;
    Image volPNG;
    Image speedPNG;
    
    Rectangle<float> crossfaderThumUpdate;
    Rectangle<float> volFaderThumUpdate1;
    Rectangle<float> volFaderThumUpdate2;
    Rectangle<float> speedFaderThumUpdate1;
    Rectangle<float> speedFaderThumUpdate2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainGUI)
};
