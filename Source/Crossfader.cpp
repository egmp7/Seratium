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
faderA(1.0f),
faderB(1.0f),
mainGainA(1.0f),
mainGainB(1.0f)
{
    addAndMakeVisible(crossfaderSlider);
    crossfaderSlider.addListener(this);
    crossfaderSlider.setRange(0.0f, 1.0f);
    crossfaderSlider.setValue(0.5f);
    crossfaderSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    player1->setGain(mainGainA);
    player2->setGain(mainGainB);
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
    if (slider == &crossfaderSlider)
        mainGainAlgorithm();
}

void Crossfader::setFaderGain(float gain, String deckID)
{
    if(deckID == "deckGUI1")
        faderA = gain;
    else
        faderB = gain;
    
    mainGainAlgorithm();
}

void Crossfader::mainGainAlgorithm()
{
    float crossfaderValue = crossfaderSlider.getValue();
    
    if(crossfaderValue < 0.5f)
    {
        mainGainA = faderA;
        mainGainB = faderB * (2.0f * crossfaderValue);
    }
    else{
        mainGainB = faderB;
        mainGainA = faderA * (-2.0f * crossfaderValue + 2.0f);
    }
    setPlayersGain();
}

void Crossfader::setPlayersGain()
{
    player1->setGain(mainGainA);
    player2->setGain(mainGainB);
}


