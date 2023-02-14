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

    g.setColour (Colour(60,21,108));
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 20.0f);

    g.setColour (Colour(41,225,35));
    g.setFont (16.0f);
    g.drawText (Format::floatToTime(time), getLocalBounds(),
                Justification::centred, true);
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

