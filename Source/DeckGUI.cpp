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
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse)
:
waveformDisplay(formatManagerToUse, cacheToUse),
player(_player)
                   
{
    // Add Buttons and Sliders
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(deckAnimation);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.1, 5.0);
    posSlider.setRange(0.0, 1.0);
    
    //volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);

    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    volSlider.setTextValueSuffix("Hello World!");
    
    volLabel.setText("Volume", dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);
    
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::purple);
    getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colours::red);

    startTimer(20);
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
    
    double rowH = getHeight() / 10;
    
    // GUI Components            x      y          width        height
    playButton.setBounds        (0,     0,         getWidth(),  rowH);
    stopButton.setBounds        (0,     rowH,      getWidth(),  rowH);
    loadButton.setBounds        (0,     rowH*7,    getWidth(),  rowH);
    volSlider.setBounds         (100,     rowH * 2,  getWidth(),  rowH);
    speedSlider.setBounds       (0,     rowH * 3,  getWidth(),  rowH);
    posSlider.setBounds         (0,     rowH * 4,  getWidth(),  rowH);
    waveformDisplay.setBounds   (0,     rowH * 5,  getWidth(),  rowH*2);
    deckAnimation.setBounds     (0,     rowH * 8,   getWidth(), rowH * 2);

}

//==============================================================================

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
    if (button == &loadButton)  // open the file chooser
    {
        // get flag integer
        int fileChooserFlags = FileBrowserComponent::canSelectFiles;
        
        // launch file browser window async
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            // get chosen file
            juce::File chosenFile = chooser.getResult();
            // load audio file
            player->loadURL(juce::URL{chosenFile});
            // load waveform display
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
        player->loadURL(URL{File{files[0]}});
        waveformDisplay.loadURL(URL{File{files[0]}});
        
    }

}
void DeckGUI::timerCallback()
{
    // Set position of the waveform line
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    // Set position of the deck animation
    deckAnimation.setPosition(player->getPosition());
}

