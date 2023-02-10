/*
  ==============================================================================

    FadersLookAndFeel.cpp
    Created: 10 Feb 2023 4:47:29pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "FadersLookAndFeel.h"

FadersLookAndFeel::FadersLookAndFeel(FaderType _faderType)
:
faderType(_faderType)
{

}

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
    // draw custom background for sliders
    
    if(faderType == FaderType::horizontal)
    {
        g.setColour(Colours::white);
        drawVerticalSticks(g, x, y, width, height);
        g.setColour(Colours::grey);
        g.fillRect(sliderHorizontalBackgroundRectangle(x, y, width, height));
    }
    if(faderType == FaderType::vertical)
    {
        //std::cout << width <<
        
        g.setColour(Colours::white);
        drawHorizontalSticks(g, x, y, width, height);
        g.setColour(Colours::grey);
        g.fillRect(sliderVerticalBackgroundRectangle(x, y, width, height));
    }
    
}

Rectangle<int> FadersLookAndFeel::sliderHorizontalBackgroundRectangle (int x, int y, int width, int height, float scale)
{
    int sliderBackgroundHeight = 8.0f;
    
    float scaleDifference = 1.0f - scale;
    int midY = y+height/2;
    
    return Rectangle<int> (x + width * scaleDifference/2,
                           midY - sliderBackgroundHeight/2,
                           width * scale,
                           sliderBackgroundHeight);
}

Rectangle<int> FadersLookAndFeel::sliderVerticalBackgroundRectangle (int x, int y, int width, int height, float scale)
{
    int sliderBackgroundWidth = 8.0f;
    
    float scaleDifference = 1.0f - scale;
    int midX = x + width/2;
    
    return Rectangle<int> (midX - sliderBackgroundWidth/2,
                           y + height * scaleDifference/2,
                           sliderBackgroundWidth,
                           height * scale);
}



void FadersLookAndFeel::drawVerticalSticks(Graphics &g , int x, int y , int width, int height)
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

void FadersLookAndFeel::drawHorizontalSticks(Graphics &g , int x, int y , int width, int height)
{
    float stickHeight = 1.0f;
    
    for (int i = 1 ; i < 8 ;  ++i)
    {
        int stickWidth;
        
        if(i % 2 == 0)
            stickWidth = width / 10 * 6;
        else
            stickWidth = width / 10 * 4;
        
        g.fillRect(Rectangle<int>(width / 2 - stickWidth/2 + x,
                                  y + height / 8 * i,
                                  stickWidth,
                                  stickHeight));
    }
}
