/*
  ==============================================================================

    RectanglesUtility.cpp
    Created: 10 Feb 2023 3:21:51pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "RectanglesUtility.h"

Rectangle<float> RectanglesUtility::catchHorizontalThumRectangle(int x, int y, int width, int height, float sliderPos, float scale)
{
    int sliderHeigth = 30.0f;
    int sliderWidth = 53.3333f;
    
    float scaleDifference = 1.0f - scale;
    int midY = y+height/2;
    
    int max = x + width;
    int min = x;

    float m = 1.0f/(max - min);
    float b = (float) - min / (float)(max -min);
    
    float relativeSliderPosition = m * sliderPos + b;
    
    return Rectangle<float> (
        (((max - min - scaleDifference * width) * relativeSliderPosition) +( min + scaleDifference * width / 2)) - sliderWidth/2 ,
        midY - sliderHeigth/2,
        sliderWidth,
        sliderHeigth);
    
}

Rectangle<float> RectanglesUtility::catchVerticalThumRectangle(int x, int y, int width, int height, float sliderPos, float scale)
{
    int sliderWidth = 30.0f;
    int sliderHeight = 53.3333f;
    
    int midX = x + width/2;

    return Rectangle<float> (
        midX - sliderWidth/2,
        y + height - sliderPos * height - sliderHeight/2,
        sliderWidth,
        sliderHeight);
}
