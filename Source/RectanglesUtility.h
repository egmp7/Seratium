/*
  ==============================================================================

    RectanglesUtility.h
    Created: 10 Feb 2023 3:21:51pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;
using namespace std;

class RectanglesUtility
{
public:
    /**Returns a rectangle based in horizontal sliders position**/
    static Rectangle<float> catchHorizontalThumRectangle(int x, int y, int width, int height, float sliderPos, float scale =1.0f);
    
    /**Returns a rectangle based in horizontal sliders position**/
    static Rectangle<float> catchVerticalThumRectangle(int x, int y, int width, int height, float sliderPos, float scale =1.0f);
};


