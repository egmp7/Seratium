/*
  ==============================================================================

    TrackName.cpp
    Created: 13 Feb 2023 2:30:53am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackName.h"

//==============================================================================
TrackName::TrackName()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TrackName::~TrackName()
{
}

void TrackName::paint (juce::Graphics& g)
{


    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (fileName, getLocalBounds(),
                juce::Justification::centredLeft, true);
}

void TrackName::resized()
{

}

void TrackName::setFileName(String _fileName)
{
    if(fileName != _fileName && !_fileName.isEmpty())
    {
        fileName = _fileName;
        repaint();
    }
}
