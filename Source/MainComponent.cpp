#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 600);

    // permissions
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (0, 2);
    }

    addAndMakeVisible(mainGUI);
    
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================

// Audio life cycle

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // delegate to DJAudioPlayer
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    // plug sources into the mixer
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    mainGUI.setBounds(getLocalBounds());
}


