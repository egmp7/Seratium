/*
  ==============================================================================

    TimeTracker.cpp
    Created: 5 Feb 2023 12:01:09pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeTracker.h"

//==============================================================================
TimeTracker::TimeTracker()
{

}

TimeTracker::~TimeTracker()
{
}

void TimeTracker::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    // draw timeTracker 
    g.setColour(Colours::white);
    g.drawText(String(currentTime) + "s", currentTimeRect, Justification::centred);
    g.drawText(String(remainingTime) + "s", remainingTimeRect, Justification::centred);

}

void TimeTracker::resized()
{
    currentTimeRect.setBounds  (0,
                                0,
                                getWidth(),
                                getHeight()/2);
    remainingTimeRect.setBounds(0,
                                getHeight()/2,
                                getWidth(),
                                getHeight()/2);
}
void TimeTracker::setCurrentTime(int time)
{
    if(currentTime != time && time != 0)
    {
        currentTime = time;
    }
}

void TimeTracker::setRemainingTime(int trackLength)
{
    if(trackLength != 0)
    {
        remainingTime = trackLength - currentTime;
        repaint();
    }
}

