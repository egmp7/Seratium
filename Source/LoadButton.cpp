/*
  ==============================================================================

    LoadButton.cpp
    Created: 13 Feb 2023 1:55:48am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LoadButton.h"

//==============================================================================
LoadButton::LoadButton(DJAudioPlayer* _player,
                       WaveformDisplay* _waveform,
                       TrackName* _trackName)
:
player(_player),
waveform(_waveform),
trackName(_trackName)
{
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setImages(
          true,
          true,
          true,
          ImageFileFormat::loadFrom(
                File("/Users/erickgonzalez/Documents/Programs/Seratium/Assets/load.png")),
          0.8f,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite,
          Image{},
          1.0,
          Colours::transparentWhite);

}

LoadButton::~LoadButton()
{
}

void LoadButton::paint (juce::Graphics& g)
{
}

void LoadButton::resized()
{
    loadButton.setBounds(getLocalBounds());
}

void LoadButton::buttonClicked(Button *)
{
    //get flag integer
    int fileChooserFlags = FileBrowserComponent::canSelectFiles;

    // launch file browser window async
    fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
    {
        // get chosen file
        File file = chooser.getResult();
        if(file.exists())
        {
            // load audio file
            player->loadURL(URL{file});
            // load waveform display
            waveform->loadURL(URL{file});
            // store fileName
            trackName->setFileName(file.getFileName());
        }
    });
}
