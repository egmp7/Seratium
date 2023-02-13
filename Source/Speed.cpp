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
    speedSlider.setRange(0.5f, 1.5f);
}

Speed::~Speed()
{
}

void Speed::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void Speed::resized()
{
    speedSlider.setBounds(getLocalBounds());
}

void Speed::sliderValueChanged(Slider* slider)
{
    //
}
