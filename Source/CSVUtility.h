/*
  ==============================================================================

    CSVUtility.h
    Created: 8 Feb 2023 1:31:16am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include <iostream>
#include <fstream>
#include "TrackEntry.h"

using namespace std;

class CSVUtility {
    
public:
    
    /**Stores the playlist as a CSV file**/
    static void save();
    /**Reads a CSV file in a playlist format**/
    static vector<TrackEntry> read();
    /**Static memory to reference playlist vector**/
    static vector<TrackEntry>* playlist;

private:
    
    /**Returns a string with  track data */
    static String createLine(TrackEntry track);
    /**Algorithm to tokenise a string */
    static vector<string> tokenise(string csvLine, char separator);
    /**Returns an instance of TrackEntry from the data provided*/
    static TrackEntry stringsToTrackEntry(vector<string> tokens);

};
