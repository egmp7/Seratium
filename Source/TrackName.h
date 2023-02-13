/*
  ==============================================================================

    TrackName.h
    Created: 13 Feb 2023 2:30:53am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class TrackName  : public Component
{
public:
    TrackName();
    ~TrackName() override;

    void paint (Graphics&) override;
    void resized() override;
    /**Set Filename
     @param _filename string **/
    void setFileName(String _fileName);

private:
    
    String fileName;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackName)
};
