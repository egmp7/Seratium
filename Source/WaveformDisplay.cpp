/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 12 Jan 2023 11:22:30pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

#include <iostream>

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse,
                                 AudioThumbnailCache & cacheToUse,
                                 DJAudioPlayer* _player,
                                 CueButton* _cueButton)
 :
fileLoaded(false),
playheadPosition(0),
audioThumb(1000,formatManagerToUse, cacheToUse),
player(_player),
cueButton(_cueButton)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
    
}

void WaveformDisplay::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);
    if (fileLoaded) // file loaded
    {
        // draw thumbnail
        audioThumb.drawChannel(g,
                               getLocalBounds(),            // get size
                               0,                           // start
                               audioThumb.getTotalLength(), // end
                               0,                           // channel 0
                               1.0f);                       // boost size
        // draw playhead
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(playheadPosition * getWidth(), 0, 1, getHeight());;
    }
    else    // file not loaded
    {
        g.setFont (20.0f);
        g.drawText ("File not loaded...",
                    getLocalBounds(),
                    Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    
}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    cout << "WaveformDisplay::changeListenerCallback Changed received" << endl;
    repaint();
}

void WaveformDisplay::loadURL(URL audioURL)
{
    std::cout << "WaveformDisplay::loadURL" << std::endl;
    
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL)); // return boolean
    
    if (fileLoaded)
    {
        std::cout << "WaveformDisplay::loadURL loaded!" << std::endl;
    }
    else
    {
        std::cout << "WaveformDisplay::loadURL not loaded!" << std::endl;
    }
    
}

void WaveformDisplay::setPlayheadPosition(double pos)
{
    if (pos != playheadPosition && !isnan(pos))
    {
        playheadPosition = pos;
        repaint();
    }
}

void WaveformDisplay::mouseDown(const MouseEvent &event)
{
    // get mouse position from component
    Point <int> p = event.getMouseDownPosition();
    // get relative position
    float relativePosition = (float)p.getX()/(float)getWidth();
    // set relative position in player
    player->setPositionRelative(relativePosition);
    //reset cueCounter
    cueButton->resetCueCounter();
}

