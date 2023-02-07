/*
  ==============================================================================

    TrackEntry.h
    Created: 7 Feb 2023 1:32:31pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace std;
using namespace juce;

class TrackEntry
{
public:
    TrackEntry(File _file,
               String _name,
               String _extension,
               String _path,
               float _duration);
    
    File file;
    String name;
    String extension;
    String path;
    float duration;
    
};
