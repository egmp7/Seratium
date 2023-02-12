/*
  ==============================================================================

    FaderModel.cpp
    Created: 11 Feb 2023 12:10:48am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "Fader.h"

Fader::Fader(
             FaderOrientation _orientation,
             Image _image)
:

orientation(_orientation),
image(_image)
{
    
}

Rectangle<float> Fader::getPosition()
{
    return position;
}

void Fader::setPosition(float sliderValue)
{
    
}

void Fader::setBounds(Rectangle<int> _bounds)
{
    bounds = _bounds;
}

Rectangle<int> Fader::getBounds()
{
    return bounds;
}




FLookAndFeel::FLookAndFeel(Image _thumbImage)
:
thumbImage(_thumbImage)
{
    
}

void FLookAndFeel::drawLinearSlider(Graphics &g,
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
    
    // draw custom slider
    g.setColour(Colours::white);
    for (Rectangle<int> line : lines())
        g.drawRect(line);
    g.setColour(Colours::darkgrey);
    g.fillRoundedRectangle(backgroundRectangle(), 2.0f);
    g.setColour(Colours::grey);
    g.fillRoundedRectangle(trackRectangle(), 2.0f);
    g.setColour(Colours::green);
    g.drawImage(thumbImage, thumbRectangle(),RectanglePlacement());
            
}

Rectangle<float> FLookAndFeel::backgroundRectangle ()
{
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        // vertical slider
        int backgroundWidth = 6.0f;
        int midX = *width/2;
        
        return Rectangle<float> (midX - backgroundWidth/2,
                                *y,
                                backgroundWidth,
                                *height);
    }
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        // horizontal slider
    }
    
    return Rectangle<float>{};
}

Rectangle<float> FLookAndFeel::trackRectangle ()
{
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        // vertical slider
        int backgroundWidth = 6.0f;
        int midX = *width/2;
        
        return Rectangle<float> (midX - backgroundWidth/2,
                                *sliderPos,
                                backgroundWidth,
                                 *y + *height - *sliderPos);
    }
    
    return Rectangle<float>{};
}

vector<Rectangle<int>> FLookAndFeel::lines()
{
    vector<Rectangle<int>> lines;
    
    for (int i = 1 ; i < 8 ;  ++i)
    {
        if(sliderStyle == Slider::SliderStyle::LinearVertical)
        {
            int lineWidth;
            int lineHeight = 1;
            float ratio = 0.6f;
            
            if(i % 2 == 0)
                lineWidth = *width * ratio;
            else
                lineWidth = *width * ratio * 0.7f;
            
            Rectangle<int> line {
                *width / 2 - lineWidth/2,
                *y + *height / 8 * i,
                lineWidth,
                lineHeight} ;
            
            lines.push_back(line);
        }
        if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
        {
            // horizontal slider
        }
        
    }
    
    return lines;
}

Rectangle<float> FLookAndFeel::thumbRectangle()
{
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        float scale = 0.7f;
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
        // horizontal slider
    }
    
    return Rectangle<float>{};
}

int FLookAndFeel::constrainSliderPos()
{
    if (sliderStyle == Slider::SliderStyle::LinearVertical)
    {
        float c = 0.08f;
        int min = *y + *height * c;
        int max = *y + *height - *height * c;
        
        if(*sliderPos < min)
            return min;
        if(*sliderPos > max)
            return max;
        return *sliderPos;
    }
    
    if (sliderStyle == Slider::SliderStyle::LinearHorizontal)
    {
        // horizontal slider
    }
    
    return *sliderPos;
    
}
