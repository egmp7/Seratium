/*
  ==============================================================================

    TrackEntry.cpp
    Created: 7 Feb 2023 1:32:31pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "TrackEntry.h"

TrackEntry::TrackEntry(File _file,
                       String _name,
                       String _extension,
                       String _path,
                       float _duration)
:
file(_file),
name(_name),
extension(_extension),
path(_path),
duration(_duration)
{
    
}
