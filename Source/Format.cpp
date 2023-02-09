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
        
    if(seconds < 10)
        return to_string(minutes)+ ":" + "0" +to_string(seconds) ;
    else
        return to_string(minutes)+ ":" +to_string(seconds);
}

