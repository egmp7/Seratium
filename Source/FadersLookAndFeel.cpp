/*
  ==============================================================================

    FadersLookAndFeel.cpp
    Created: 10 Feb 2023 4:47:29pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "FadersLookAndFeel.h"

void FadersLookAndFeel::drawLinearSlider(Graphics &g,
                                                   int x,
                                                   int y,
                                                   int width,
                                                   int height,
                                                   float sliderPos,
                                                   float minSliderPos,
                                                   float maxSliderPos,
                                                   const Slider::SliderStyle,
                                                   Slider &)
{

    // background thumb
    g.setColour(Colours::white);
    drawSticks(g, x, y, width, height);
    g.setColour(Colours::grey);
    g.fillRect(sliderBackgroundRectangle(x, y, width, height));
    
}

Rectangle<int> FadersLookAndFeel::sliderBackgroundRectangle (int x, int y, int width, int height, float scale)
{
    int sliderBackgroundHeight = 8.0f;
    
    float scaleDifference = 1.0f - scale;
    int midY = y+height/2;
    
    return Rectangle<int> (x + width * scaleDifference/2,
                           midY - sliderBackgroundHeight/2,
                           width * scale,
                           sliderBackgroundHeight);
}



void FadersLookAndFeel::drawSticks(Graphics &g , int x, int y , int width, int height)
{
    float stickWidth = 1.0f;
    
    for (int i = 1 ; i < 8 ;  ++i)
    {
        int stickHeigth;
        
        if(i % 2 == 0)
            stickHeigth = height / 10 * 6;
        else
            stickHeigth = height / 10 * 4;
        
        g.fillRect(Rectangle<int>( x + width / 8 * i,
                                  height / 2 - stickHeigth /2,
                                  stickWidth,
                                  stickHeigth));
    }
}
