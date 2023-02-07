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
Playlist::Playlist(DJAudioPlayer* _player1,
                   DJAudioPlayer* _player2,
                   DeckGUI* _deckGUI1,
                   DeckGUI* _deckGUI2,
                   AudioFormatManager & _formatManagerToUse)
:
player(_formatManagerToUse),
player1(_player1),
player2(_player2),
deckGUI1(_deckGUI1),
deckGUI2(_deckGUI2)
{
    addAndMakeVisible(tableComponent);
                                        // name             id  width
    tableComponent.getHeader().addColumn("A",               1,  50);
    tableComponent.getHeader().addColumn("B",               2,  50);
    tableComponent.getHeader().addColumn("Track title",     3,  300);
    tableComponent.getHeader().addColumn("Length",          4,  80);
    tableComponent.getHeader().addColumn("Path",            5,  400);
    tableComponent.getHeader().addColumn("Extension",       6,  80);

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
    searchComponent.setBounds(0, 0, 300, 50);
}

//==============================================================================

int Playlist::getNumRows()
{
    return (int) tracksView.size();
}

void Playlist::paintRowBackground (Graphics & g,
             int rowNumber,
             int width,
             int height,
             bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
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
    if (columnId == 3)
    {
        g.drawText(tracksView[rowNumber].name,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 4)
    {
        g.drawText(String{tracksView[rowNumber].duration},
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 5)
    {
        g.drawText(tracksView[rowNumber].path,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    if (columnId == 6)
    {
        g.drawText(tracksView[rowNumber].extension,
                   2, 0,
                   width-4,
                   height,
                   Justification::centredLeft,
                   true);
    }
}

Component* Playlist::refreshComponentForCell (int rowNumber,
            int columnId,
            bool isRowSelected,
            Component *existingComponentToUpdate)
{
    if(columnId ==1)
    {
        if(existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{"A"};
            
            String id {to_string(rowNumber)};
            
            btn->setComponentID(id);
            btn->setName("A");
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    if(columnId ==2)
    {
        if(existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{"B"};
            
            String id {to_string(rowNumber)};
            
            btn->setComponentID(id);
            btn->setName("B");
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void Playlist::buttonClicked (Button* button)
{
    int id = stoi(button->getComponentID().toStdString());
    
    if(button->getName() == "A")
    {
        player1->loadURL(URL{tracksView[id].file});
        deckGUI1->loadWaveform(tracksView[id].file);
    }
    else
    {
        player2->loadURL(URL{tracksView[id].file});
        deckGUI2->loadWaveform(tracksView[id].file);
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
        if (!checkFileInTracks(file)) // create a new file
        {
            player.loadURL(URL{File{file}});
            
            TrackEntry track{
                File{file},
                File{file}.getFileNameWithoutExtension(),
                File{file}.getFileExtension(),
                File{file}.getFullPathName(),
                (float)player.getTrackLength()};
            
            tracks.push_back(track);
            player.releaseResources();
        }
        else // do not create a new file
            continue;
    }
    
    // copy of tracks vector
    tracksView = tracks;
    
    // update table
    tableComponent.updateContent();
}

bool Playlist::checkFileInTracks(String path)
{
    for (TrackEntry track : tracks)
    {
        if(track.path == (path))
            return true;
    }
    return false;
}

var Playlist::getDragSourceDescription ( const SparseSet< int > & currentlySelectedRows)
{
    cout<< "Playlist::getDragSourceDescription" <<endl;
    
    String filePath = tracksView[currentlySelectedRows[0]].path;
    return filePath;
}

void Playlist::textEditorTextChanged (TextEditor & textEditor)
{
    tracksView.clear();
    
    // search in tracks
    for (TrackEntry track : tracks)
    {
        if(track.name.containsIgnoreCase(textEditor.getText()))
        {
            tracksView.push_back(track);
        }
    }
    
    tableComponent.updateContent();
}
