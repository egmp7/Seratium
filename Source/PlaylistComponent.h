/*
  ==============================================================================

    PlaylistComponent.h
    Created: 14 Jan 2023 1:21:11pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

using namespace std;

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    void paintRowBackground (juce::Graphics &,
                             int rowNumber,
                             int width,
                             int height,
                             bool rowIsSelected) override;
    
    void paintCell (juce::Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    juce::Component* refreshComponentForCell (int rowNumber,
                                              int columnId,
                                              bool isRowSelected,
                                              juce::Component *existingComponentToUpdate);
    
    void buttonClicked (juce::Button* button) override;

private:
    
    juce::TableListBox tableComponent;
    vector<string> trackTitles;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
