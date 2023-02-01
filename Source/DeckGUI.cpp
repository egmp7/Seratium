/*
  ==============================================================================

    DeckGUI.cpp
    Created: 12 Jan 2023 7:05:21pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse)
                 : player(_player),
                 waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Add Buttons and Sliders
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.1, 5.0);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    double rowH = getHeight() / 8;
    
    // buttons
    playButton.setBounds(0, 0, getWidth(),rowH);
    stopButton.setBounds(0, rowH, getWidth(),rowH);
    loadButton.setBounds(0, rowH*7, getWidth(),rowH);
    
    // slider
    volSlider.setBounds(0,  rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0,  rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0,  rowH * 4, getWidth(), rowH);
    
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH*2);
    
    volSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);

}

/** Process user click
 @param button juce::Button*/
void DeckGUI::buttonClicked(juce::Button* button)
{
    if(button == &playButton)
    {
        player->start();

    }
    if (button == &stopButton)
    {
        player->stop();
    }

    if (button == &loadButton)
    {
        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
        auto fileChooserFlags =
        juce::FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that.
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File chosenFile = chooser.getResult();
            player->loadURL(juce::URL{chosenFile});
            waveformDisplay.loadURL(juce::URL{chosenFile});
        });
    }
}

/** Process user silder action
 @param button juce::Button*/
void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag (const juce::StringArray &files)
{
    std::cout<< "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    std::cout<< "DeckGUI::filesDropped" << std::endl;
    
    if (files.size() ==1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }

}
void DeckGUI::timerCallback()
{
    
    //std::cout << isnan(player->getPositionRelative()) << std::endl;
    
    waveformDisplay.setPositionRelative(
                    player->getPositionRelative());
}

