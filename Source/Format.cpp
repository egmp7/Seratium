/*
  ==============================================================================

    Format.cpp
    Created: 7 Feb 2023 5:18:38pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "Format.h"

string Format::floatToTime(float time)
{
    int minutes = time / 60;
    int seconds = (int)time % 60;
    
    string min,sec,mili;

    min = to_string(minutes);
    sec = to_string(seconds);
    mili = to_string(time - minutes * 60 - seconds).substr(2,2);
    
    if(seconds < 10)
        return min + ":" + "0" + sec +":" + mili ;
    else
        return min + ":" + sec + ":" + mili;
}


