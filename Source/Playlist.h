/*
  ==============================================================================

    Playlist.h
    Created: 14 Jan 2023 1:21:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

#include "DJAudioPlayer.h"
#include "DeckGUI.h"

using namespace std;
using namespace juce;

//==============================================================================

class Playlist  : public Component,
                  public TableListBoxModel,
                  public Button::Listener,
                  public FileDragAndDropTarget
{
public:
    Playlist(DJAudioPlayer* _player1,
             DJAudioPlayer* _player2,
             DeckGUI* _deckGUI1,
             DeckGUI* _deckGUI2,
             AudioFormatManager & _formatManagerToUse);
    
    ~Playlist() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    
    void paintRowBackground (Graphics & g,
                    int rowNumber,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    void paintCell (Graphics & g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    Component* refreshComponentForCell (int rowNumber,
                    int columnId,
                    bool isRowSelected,
                    Component *existingComponentToUpdate) override ;
    
    void buttonClicked (juce::Button* button) override;
    
    /**Checks when user hover the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Runs when the user release the click*/
    void filesDropped (const StringArray &files, int x, int y) override;
    

private:
    
    DJAudioPlayer player;
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
    TableListBox tableComponent;
    vector<File> tracks;
    vector<float> tracksDuration;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Playlist)
};
