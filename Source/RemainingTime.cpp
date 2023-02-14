/*
  ==============================================================================

    remainingTime.cpp
    Created: 12 Feb 2023 8:04:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RemainingTime.h"

//==============================================================================
RemainingTime::RemainingTime()
{

}

RemainingTime::~RemainingTime()
{
}

void RemainingTime::paint (Graphics& g)
{
    g.setColour (Colour(60,21,108));
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 20.0f);

    if (remainingTime == 0)
        g.setColour (Colours::darkgrey);
    else
        g.setColour (Colours::orange);
    g.setFont (14.0f);
    g.drawText (Format::floatToTime(remainingTime), getLocalBounds(),
                Justification::centred, true);
}

void RemainingTime::resized()
{

}

void RemainingTime::setTime(float _time)
{
    if(time != _time && !isnan(_time))
    {
        time = _time;
        update();
    }
}
void RemainingTime::setTrackLength(float _trackLength)
{
    if(trackLength != _trackLength && !isnan(_trackLength))
    {
        trackLength = _trackLength;
        update();
    }
}

void RemainingTime::update()
{
    remainingTime = trackLength - time;
    repaint();
}

