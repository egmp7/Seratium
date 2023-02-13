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
#include "CSV.h"

using namespace std;
using namespace juce;

//==============================================================================

class Playlist  : public Component,
                  public TableListBoxModel,
                  public FileDragAndDropTarget,
                  public DragAndDropContainer,
                  public TextEditor::Listener
{
public:
    Playlist(AudioFormatManager & _formatManagerToUse);
    
    ~Playlist() override;

    void paint (Graphics&) override;
    void resized() override;
    /**Returns the number of rows in the table**/
    int getNumRows() override;
    /**Paints row background
     @param g Graphic object
     @param rowNumber the number of row of the table
     @param width not used
     @param height not used
     @param rowIsSelected true when user clicks a row in the table*/
    void paintRowBackground (Graphics & g,
                    int rowNumber,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    /**Prints data in the table
     @param g Graphic object
     @param rowNumber number of row in the table
     @param columnId number of the column in the table
     @param width not used
     @param height not used
     @param rowIsSelected true when user clicks a row in the table*/
    void paintCell (Graphics & g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    /**Checks drag and drop  system files when entering the component rectangle
     @param &files an array of files  selected when dragging
     @returns true when item is inside the component*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    /**Checks for drag and drop object sources
     @param &dragSourceDetails contains file names
     @returns true when item is inside the component */
    void filesDropped (const StringArray &files, int x, int y) override;
    /**Creates a DragAndDropContainer from table cell
     @param &currentlySelectedRows file selected
     @returns string with the filePath */
    var getDragSourceDescription ( const SparseSet< int > & currentlySelectedRows) override;
    /**Search in the playlist
     @param textEditor object methods from text editor*/
    void textEditorTextChanged (TextEditor &) override;
    /**deletes a track in the playlist when pressing the delete key 
     @param lastRowSelected**/
    void deleteKeyPressed (int lastRowSelected) override;
    
private:
    
    /**Checks if a file already exists in tracks vector
     @param path to be compared with playlist vector*/
    bool checkFileInPlaylist(String path);
    
    // Controller
    DJAudioPlayer player;
    
    // Components
    TableListBox tableComponent;
    TextEditor searchComponent{"search"};
    Label labelSearch{"searchCoponent","Search"};
    Rectangle<int> title;
    
    vector<TrackEntry> playlist;
    vector<TrackEntry> playlistView;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Playlist)
};
