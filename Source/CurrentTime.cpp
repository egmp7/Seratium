/*
  ==============================================================================

    currentTime.cpp
    Created: 12 Feb 2023 8:03:12pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CurrentTime.h"

//==============================================================================
CurrentTime::CurrentTime()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CurrentTime::~CurrentTime()
{
}

void CurrentTime::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("currentTime", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void CurrentTime::resized()
{
    
}
