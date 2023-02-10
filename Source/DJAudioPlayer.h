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
    
    
    /**Prepares an audio URL for playback
     @param audioURL file to be loaded*/
    void loadURL(URL audioURL);
    /**Set gain of audio
     @param gain value*/
    void setGain(double gain);
    /**Set speed of audio
     @param ratio value*/
    void setSpeed(double ratio);
    /**Set position in seconds of audio
     @param posInSeconds value in seconds of the position of the player*/
    void setPosition(double posInSeconds);
    /**Set relative position of audio
     @param pos value in seconds of the position of the player*/
    void setPositionRelative(double pos);
    /**Start audio playback*/
    void start();
    /**Stop audio playback*/
    void stop();
    /**get the position of the track in seconds
     @returns position in seconds**/
    double getPosition();
    /**get relative position of the playhead
     @returns a value between 0 and 1*/
    double getPositionRelative();
    /**get  track  length in seconds
     @returns track length in seconds*/
    double getTrackLength();
    /**Checks if player is playing
     @returns true if the player is playing*/
    bool isPlaying();

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
