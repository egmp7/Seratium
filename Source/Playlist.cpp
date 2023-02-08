/*
  ==============================================================================

    Playlist.cpp
    Created: 14 Jan 2023 1:21:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Playlist.h"

//==============================================================================
Playlist::Playlist(AudioFormatManager & _formatManagerToUse)
:
player(_formatManagerToUse)
{
    addAndMakeVisible(tableComponent);
                                        // name             id  width
    tableComponent.getHeader().addColumn("#",               1,  25);
    tableComponent.getHeader().addColumn("Track title",     2,  300);
    tableComponent.getHeader().addColumn("Length",          3,  80);
    tableComponent.getHeader().addColumn("Path",            4,  400);
    tableComponent.getHeader().addColumn("Extension",       5,  80);

    tableComponent.setModel(this);
    
    addAndMakeVisible(searchComponent);
    searchComponent.addListener(this);
    
}

Playlist::~Playlist()
{
}

void Playlist::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void Playlist::resized()
{

    tableComponent.setBounds(getLocalBounds());
    searchComponent.setBounds(getWidth() -300, 0, 300, 26);
}

//==============================================================================

int Playlist::getNumRows()
{
    return (int) playlistView.size();
}

void Playlist::paintRowBackground (Graphics & g,
             int rowNumber,
             int width,
             int height,
             bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(Colours::orange);
    else
    {
        if(rowNumber % 2 == 0)
            g.fillAll(Colours::darkgrey);
        else
            g.fillAll(Colours::grey);
    }
}

void Playlist::paintCell (Graphics & g,
            int rowNumber,
            int columnId,
            int width,
            int height,
            bool rowIsSelected)
{
    if (columnId == 1)
    {
        g.drawText(String{rowNumber+1},
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 2)
    {
        g.drawText(playlistView[rowNumber].name,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 3)
    {
        g.drawText(Format::floatToTime(playlistView[rowNumber].duration)+"s",
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 4)
    {
        g.drawText(playlistView[rowNumber].path,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 5)
    {
        g.drawText(playlistView[rowNumber].extension,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
}
bool Playlist::isInterestedInFileDrag (const StringArray &files)
{
    cout << "Playlist::isInterestedInFileDrag" << endl;
    return true;
}

void Playlist::filesDropped (const StringArray &files, int x, int y)
{
    for (String file : *&files)
    {
        if (!checkFileInPlaylist(file)) // create a new file
        {
            player.loadURL(URL{File{file}});
            
            TrackEntry track{
                File{file},
                File{file}.getFileNameWithoutExtension(),
                File{file}.getFileExtension(),
                File{file}.getFullPathName(),
                (float)player.getTrackLength()};
            
            playlist.push_back(track);
            player.releaseResources();
        }
        else // do not create a new file
            continue;
    }
    
    // copy of playlist vector
    playlistView = playlist;
    
    // update table
    tableComponent.updateContent();
}

bool Playlist::checkFileInPlaylist(String path)
{
    for (TrackEntry track : playlist)
    {
        if(track.path == (path))
            return true;
    }
    return false;
}

var Playlist::getDragSourceDescription ( const SparseSet< int > & currentlySelectedRows)
{
    cout<< "Playlist::getDragSourceDescription" <<endl;
    
    String filePath = playlistView[currentlySelectedRows[0]].path;
    return filePath;
}

void Playlist::textEditorTextChanged (TextEditor & textEditor)
{
    playlistView.clear();
    
    // search in playlist
    for (TrackEntry track : playlist)
    {
        if(track.file.getFileName().containsIgnoreCase(textEditor.getText()))
        {
            playlistView.push_back(track);
        }
    }
    
    tableComponent.updateContent();
}
