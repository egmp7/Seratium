/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 11 Jan 2023 7:06:00pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager): formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer(){}

//==============================================================================
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

}
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);

}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto * reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    
    if (reader != nullptr)
    
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader,true));
    
        transportSource.setSource(newSource.get(),0,nullptr,reader->sampleRate);
        
        readerSource.reset(newSource.release());
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if(gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain setGain should be between 0 and 1"<< std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}
void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed setSpeed should be between 0 and 100.0"<< std::endl;

    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSeconds)
{
    transportSource.setPosition(posInSeconds);
}
void DJAudioPlayer::setPositionRelative(double pos)
{
    if(pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1.0"<< std::endl;

    }
    else
    {
        double posInSec = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSec);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

