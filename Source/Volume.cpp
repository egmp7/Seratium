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
Volume::Volume()
:
volumeCustomFader(
            FaderOrientation::v,
            ImageFileFormat::loadFrom(File("/Users/erickgonzalez/Documents/Programs/OtoDekcs/Assets/volFader.png")))
{
    addAndMakeVisible(volumeSlider);
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
    volumeCustomFader.setBounds(getBounds());
    
    g.fillRect(volumeCustomFader.getBounds());
    
    //cout << "Volume::paint" << volumeSlider.getValue() <<endl;


}

void Volume::resized()
{
    volumeSlider.setBounds(getLocalBounds());
}

void Volume::sliderValueChanged(Slider* slider)
{
    volumeSlider.setValue(slider->getValue());
    volumeCustomFader.setPosition(slider->getValue());
}

float Volume::getValue()
{
    return volumeSlider.getValue();
}
