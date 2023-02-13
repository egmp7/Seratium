/*
  ==============================================================================

    FaderModel.h
    Created: 11 Feb 2023 12:10:48am
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

enum FaderStyle {MidGrow,FullGrow};

class FaderLookAndFeel : public LookAndFeel_V4
{
public:
    FaderLookAndFeel(Image _thumbImage,
                     FaderStyle);
    /**Draw custom slider
    @param x left edge of component
    @param y left edge of component
    @param widht width of component
    @param height height of component
    @param sliderPos  position of the component from left up of the component*/
    void drawLinearSlider(Graphics &,
                           int _x,
                           int _y,
                           int _width,
                           int _height,
                           float _sliderPos,
                           float _minSliderPos,
                           float _maxSliderPos,
                           const Slider::SliderStyle,
                           Slider &) override;
    
private:
    
    /**creates a custom background rectangle for the slider
    @returns background rectangle*/
    Rectangle<float> backgroundRectangle ();
    /**creates a custom track rectangle for the slider
    @returns track rectangle*/
    Rectangle<float> trackRectangle ();
    /**creates a custom thumb rectangle for the slider
    @returns thumb rectangle*/
    Rectangle<float> thumbRectangle();
    /**Draws stick elements of background **/
    vector<Rectangle<int>> lines();
    /**constrains the value of the slider
     @returns constrained  sliderPos value **/
    int constrainSliderPos();
    
    Image thumbImage;
    int* x;
    int* y;
    int* width;
    int* height;
    float* sliderPos;
    Slider::SliderStyle sliderStyle;
    Slider* slider;
    FaderStyle faderStyle;
    
    
};


