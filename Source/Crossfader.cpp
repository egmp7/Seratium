/*
  ==============================================================================

    Crossfader.cpp
    Created: 4 Feb 2023 10:41:54pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Crossfader.h"

//==============================================================================
Crossfader::Crossfader(DJAudioPlayer* _player1, DJAudioPlayer* _player2)
:
player1(_player1),
player2(_player2),
volumeL(1.0f),
volumeR(1.0f)
{
    addAndMakeVisible(crossfaderSlider);
    crossfaderSlider.addListener(this);
    crossfaderSlider.setRange(0.0f, 1.0f);
    crossfaderSlider.setValue(0.5f);
    crossfaderSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
}

Crossfader::~Crossfader()
{
}

void Crossfader::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void Crossfader::resized()
{
    crossfaderSlider.setBounds(getLocalBounds());
}

void Crossfader::sliderValueChanged (Slider *slider)
{
    mixVolumesAlgorithm();
}

void Crossfader::setVolumeL(float value)
{
    volumeL = value;
    mixVolumesAlgorithm();
}

void Crossfader::setVolumeR(float value)
{
    volumeR = value;
    mixVolumesAlgorithm();
}

void Crossfader::mixVolumesAlgorithm()
{
    float crossfaderValue = crossfaderSlider.getValue();
    
    if(crossfaderValue < 0.5f)
    {
        mainVolumeL = volumeL;
        mainVolumeR = volumeR * (2.0f * crossfaderValue);
    }
    else{
        mainVolumeL = volumeL * (-2.0f * crossfaderValue + 2.0f);
        mainVolumeR = volumeR;
    }
    player1->setGain(mainVolumeL);
    player2->setGain(mainVolumeR);
}
