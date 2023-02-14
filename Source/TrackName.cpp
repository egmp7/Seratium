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
    g.setColour (Colour(60,21,108));
    g.drawRoundedRectangle(0,0,getWidth(),getHeight(), 5.0f,3.0f);

    g.setColour (Colours::orange);
    g.setFont (16.0f);
    g.drawText (" "+fileName, getLocalBounds(),
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
