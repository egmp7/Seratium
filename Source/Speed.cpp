/*
  ==============================================================================

    Speed.cpp
    Created: 11 Feb 2023 1:05:25am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Speed.h"

//==============================================================================
Speed::Speed()
{
    addAndMakeVisible(speedSlider);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    speedSlider.setValue(1.0f);
    speedSlider.setRange(0.0f, 1.0f);
    //speedSlider.setLookAndFeel(&speedLookAndFeel);
}

Speed::~Speed()
{
}

void Speed::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

   
}

void Speed::resized()
{
    speedSlider.setBounds(getLocalBounds());
}

void Speed::sliderValueChanged(Slider* slider)
{
    speedSlider.setValue(slider->getValue());
}

float Speed::getValue()
{
    return speedSlider.getValue();
}
