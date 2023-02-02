/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 11 Jan 2023 7:06:00pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

class DJAudioPlayer : public AudioSource
{
public:
    DJAudioPlayer(AudioFormatManager & _formatManager);
    ~DJAudioPlayer();
    
    //================================================================================
    
    // Audio source interface
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //================================================================================
    
    
    /**Prepares an audio URL for playback*/
    void loadURL(URL audioURL);
    /**Set gain of audio
     @param gain double*/
    void setGain(double gain);
    /**Set speed of audio
     @param ratio double*/
    void setSpeed(double ratio);
    /**Set position in seconds of audio
     @param posInSeconds double*/
    void setPosition(double posInSeconds);
    /**Set relative position of audio
     @param pos double*/
    void setPositionRelative(double pos);
    /**Start audio playback*/
    void start();
    /**Stop audio playback*/
    void stop();
    
    /**get relative position of the playhead*/
    double getPositionRelative();

private:
    
    // Audio Classes inherited from Audio Source  ONION CONCEPT
    
    AudioFormatManager & formatManager;
    unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{
        &transportSource,   // Audio Source
        false,              // Don't delete audio source
        2};                 // Two channels
    
};
