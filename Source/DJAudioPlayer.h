/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 11 Jan 2023 7:06:00pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    
    //==================**============================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSeconds);
    void setPositionRelative(double pos);

    
    void start();
    void stop();
    
    /**get relative position of the playhead*/
    double getPositionRelative();

private:
    
    //Load Audio objects
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::FileChooser fChooser{"Select a file..."};
    
    // Audio Classes
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource,
                                               false,
                                               2};
    
};
