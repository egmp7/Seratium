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
}

CurrentTime::~CurrentTime()
{
}

void CurrentTime::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText (Format::floatToTime(time), getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void CurrentTime::resized()
{
    
}
void CurrentTime::setTime(float _time)
{
    if(time != _time && !isnan(_time))
    {
        time = _time;
        repaint();
    }
}

