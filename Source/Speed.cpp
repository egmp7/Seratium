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
Speed::Speed(DJAudioPlayer* _player)
:
player(_player)
{
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    speedSlider.setValue(1.0f);
    speedSlider.setRange(0.5f, 1.5f);
    speedSlider.setLookAndFeel(&speedLookAndFeel);
}

Speed::~Speed()
{
}

void Speed::paint (juce::Graphics& g)
{
    g.setColour (Colour(60,21,108));
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 10.0f);
}

void Speed::resized()
{
    speedSlider.setBounds(getLocalBounds());
}

void Speed::sliderValueChanged(Slider* slider)
{
    player->setSpeed(slider->getValue());
}
