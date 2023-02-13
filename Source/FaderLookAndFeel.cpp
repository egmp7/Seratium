/*
  ==============================================================================

    FaderModel.cpp
    Created: 11 Feb 2023 12:10:48am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "FaderLookAndFeel.h"

FaderLookAndFeel::FaderLookAndFeel(Image _thumbImage,
                                   FaderStyle _faderStyle)
:
thumbImage(_thumbImage),
faderStyle(_faderStyle)
{
    
}

void FaderLookAndFeel::drawLinearSlider(Graphics &g,
                                                   int _x,
                                                   int _y,
                                                   int _width,
                                                   int _height,
                                                   float _sliderPos,
                                                   float _minSliderPos,
                                                   float _maxSliderPos,
                                                   const Slider::SliderStyle _sliderStyle,
                                                   Slider &_slider)
{
    // reference component elements
    x = &_x;
    y = &_y;
    width = &_width;
    height = &_height;
    sliderPos = &_sliderPos;
    sliderStyle = _sliderStyle;
    slider = &_slider;
    
    // draw custom slider
    g.setColour(Colours::white);
    for (Rectangle<int> line : lines())
        g.drawRect(line);
    g.setColour(Colours::darkgrey);
    g.fillRoundedRectangle(backgroundRectangle(), 2.0f);
    g.setColour(Colours::grey);
    if(FaderStyle::FullGrow == faderStyle)
        g.fillRoundedRectangle(trackRectangle(), 2.0f);
    if(FaderStyle::MidGrow == faderStyle)
        g.fillRect(trackRectangle());
    g.setColour(Colours::green);
    g.drawImage(thumbImage, thumbRectangle(),RectanglePlacement());
            
}

Rectangle<float> FaderLookAndFeel::backgroundRectangle ()
{
    int size = 6;
    
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        int midX = *width/2;
        
        return Rectangle<float> (midX - size/2,
                                *y,
                                size,
                                *height);
    }
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        int midY = *height/2;
        
        return Rectangle<float> (*x,
                                 midY - size/2,
                                 *width,
                                 size);
    }
    
    return Rectangle<float>{};
}

Rectangle<float> FaderLookAndFeel::trackRectangle ()
{
    if (sliderStyle == Slider::SliderStyle::LinearVertical
        && faderStyle == FaderStyle::FullGrow)
    {
        // vertical slider
        int backgroundWidth = 6.0f;
        int midX = *width/2;
        
        return Rectangle<float> (midX - backgroundWidth/2,
                                *sliderPos,
                                backgroundWidth,
                                 *y + *height - *sliderPos);
    }
    
    if (sliderStyle == Slider::SliderStyle::LinearVertical
        && faderStyle == FaderStyle::MidGrow)
    {
        int backgroundWidth = 6.0f;
        int midX = *width/2;
        int midY = *y + *height/2;
        float range = ((float)slider->getMaximum() - (float)slider->getMinimum());
        float fX;
                
        if(slider->getValue() < range/2)
            fX = (-2 * (slider->getValue()-0.5f) +1);
        else
            fX = -(2 * (slider->getValue()-0.5f) -1);
    
        return Rectangle<float> (
                                 midX - backgroundWidth/2,
                                 midY,
                                 backgroundWidth,
                                 fX * *height/2);
    }
    
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal
        && faderStyle == FaderStyle::MidGrow)
    {
        int backgroundHeight = 6.0f;
        int midX = *x + *width/2;
        int midY = *height/2;
        float range = ((float)slider->getMaximum() - (float)slider->getMinimum());
        float fX;
        
        if(slider->getValue() < range/2)
            fX = -(-2 * slider->getValue() +1);
        else
            fX = 2 * slider->getValue() -1;
    
        return Rectangle<float> (
                                 midX,
                                 midY - backgroundHeight/2,
                                 fX * *width/2,
                                 backgroundHeight);
    }
    
    
    return Rectangle<float>{};
}

vector<Rectangle<int>> FaderLookAndFeel::lines()
{
    vector<Rectangle<int>> lines;
    
    if(sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        for (int i = 1 ; i < 6 ;  ++i)
        {
       
            int lineWidth;
            int lineHeight = 1;
            float lineWidthRatio = 0.6f;
            
            if(i % 2 == 0)
                lineWidth = *width * lineWidthRatio;
            else
                lineWidth = *width * lineWidthRatio * 0.7f;
            
            Rectangle<int> line {
                *width / 2 - lineWidth/2,
                *y + *height / 6 * i,
                lineWidth,
                lineHeight} ;
            
            lines.push_back(line);
        }
    }
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        for (int i = 1 ; i < 8 ;  ++i)
        {
            int lineWidth = 1;
            int lineHeight;
            float lineHeightRatio = 0.6f;
            
            if(i % 2 == 0)
                lineHeight = *height * lineHeightRatio;
            else
                lineHeight = *height * lineHeightRatio * 0.7f;
            
            Rectangle<int> line {
                *x + *width / 8 * i,
                *height / 2 - lineHeight/2,
                lineWidth,
                lineHeight};
            
            lines.push_back(line);
        }
    }
    return lines;
}

Rectangle<float> FaderLookAndFeel::thumbRectangle()
{
    float scale = 0.7f;

    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        int sliderWidth = 30.0f * scale;
        int sliderHeight = 53.3333f * scale;
        int midX = *width/2;
        
        return Rectangle<float> (
                                 midX - sliderWidth/2,
                                 constrainSliderPos() - sliderHeight / 2,
                                 sliderWidth,
                                 sliderHeight);
    }
    
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        int sliderWidth = 53.3333f * scale;
        int sliderHeight = 30.0f * scale;
        int midY = *height/2;
        
        return Rectangle<float> (
                                 constrainSliderPos() - sliderWidth / 2,
                                 midY - sliderHeight/2,
                                 sliderWidth,
                                 sliderHeight);
    }
    
    return Rectangle<float>{};
}

int FaderLookAndFeel::constrainSliderPos()
{
    
    int min;
    int max;
    
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        float c = 0.08f;
         min = *y + *height * c;
         max = *y + *height - *height * c;
    }
    
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        float c = 0.04f;
         min = *x + *width * c;
         max = *x + *width - *width * c;
    }
    
    if(*sliderPos < min)
        return min;
    if(*sliderPos > max)
        return max;
    return *sliderPos;
    
}
