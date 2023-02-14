/*
  ==============================================================================

    Volume.cpp
    Created: 11 Feb 2023 12:21:51am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Volume.h"

//==============================================================================
Volume::Volume(Crossfader* _crossfader)
:
crossfader(_crossfader)
{
    addAndMakeVisible(volumeSlider);
    volumeSlider.addListener(this);
    volumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volumeSlider.setValue(1.0f);
    volumeSlider.setRange(0.0f, 1.0f);
    volumeSlider.setLookAndFeel(&volumeLookAndFeel);
}

Volume::~Volume()
{
}

void Volume::paint (juce::Graphics& g)
{
    g.setColour (Colour(60,21,108));
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 10.0f);
}

void Volume::resized()
{
    volumeSlider.setBounds(getLocalBounds());
}

void Volume::sliderValueChanged(Slider* slider)
{
    if(getComponentID() == "volLeft")
        crossfader->setVolumeL(slider->getValue());
    if(getComponentID() == "volRight")
        crossfader->setVolumeR(slider->getValue());
}
