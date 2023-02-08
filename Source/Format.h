/*
  ==============================================================================

    Format.h
    Created: 7 Feb 2023 5:18:38pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Format{
public:
    Format();
    
    /**Transforms a float into a time string eg: mm:ss
     @param time float secods number
     @return string mm:ss*/
    static string floatToTime(float time);
};

