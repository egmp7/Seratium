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

class CSV {
    
public:
    
    /**Stores the playlist as a CSV file**/
    static void save();
    /**Reads a CSV file in a playlist format
     @returns tracks readed*/
    static vector<TrackEntry> read();
    /**Static memory to reference playlist vector**/
    static vector<TrackEntry>* playlist;

private:
    
    /**Returns a string with  track data
     @param track to be transformed into a string of data
     @returns a string in CSV format with track data*/
    static String createLine(TrackEntry track);
    /**Algorithm to tokenise a string
     @param csvLine string to be tokenised
     @param separator used to delimeter a column
     @returns a vector with each column in it*/
    static vector<string> tokenise(string csvLine, char separator);
    /**Returns an instance of TrackEntry from the data provided
     @param tokens columns of data
     @returns al track entrie that the playlist can read from*/
    static TrackEntry stringsToTrackEntry(vector<string> tokens);

};
