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
#include "TrackEntry.h"
#include "Format.h"

using namespace std;
using namespace juce;

//==============================================================================

class Playlist  : public Component,
                  public TableListBoxModel,
                  public Button::Listener,
                  public FileDragAndDropTarget,
                  public DragAndDropContainer,
                  public TextEditor::Listener
{
public:
    Playlist(DJAudioPlayer* _player1,
             DJAudioPlayer* _player2,
             DeckGUI* _deckGUI1,
             DeckGUI* _deckGUI2,
             AudioFormatManager & _formatManagerToUse);
    
    ~Playlist() override;

    void paint (Graphics&) override;
    void resized() override;
    /**Returns the number of rows in the table**/
    int getNumRows() override;
    /**Paints row background**/
    void paintRowBackground (Graphics & g,
                    int rowNumber,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    /**Prints data in the table**/
    void paintCell (Graphics & g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    /**Prints a functional component in a cell**/
    Component* refreshComponentForCell (int rowNumber,
                    int columnId,
                    bool isRowSelected,
                    Component *existingComponentToUpdate) override ;
    /**Loads audio track to the application **/
    void buttonClicked (Button* button) override;
    /**Checks when user hover the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Runs when the user release the click*/
    void filesDropped (const StringArray &files, int x, int y) override;
    /**Creates a DragAndDropContainer from table cell*/
    var getDragSourceDescription ( const SparseSet< int > & currentlySelectedRows) override;
    /**Search in the playlist**/
    void textEditorTextChanged (TextEditor &) override;
    
private:
    
    /**Checks if a file already exists in tracks vector**/
    bool checkFileInPlaylist(String path);
    
    DJAudioPlayer player;
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
    TableListBox tableComponent;
    
    vector<TrackEntry> playlist;
    vector<TrackEntry> playlistView;
    
    TextEditor searchComponent{"search"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Playlist)
};
