/*
  ==============================================================================

    FadersLookAndFeel.h
    Created: 10 Feb 2023 4:47:29pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class FadersLookAndFeel : public LookAndFeel_V4
{
public:
    /**Draw custom component**/
    void drawLinearSlider(Graphics &,
                               int x,
                               int y,
                               int width,
                               int height,
                               float sliderPos,
                               float minSliderPos,
                               float maxSliderPos,
                               const Slider::SliderStyle,
                               Slider &) override;
    
private:
    /**returns a triangle with a custom slider background
    @param x left edge of component
    @param y left edge of component
    @param widht width of component
    @param height height of component
    @param scale scale rectangle between 0.0f and 1.0f
    @returns banground rectangle
     */
    Rectangle<int> sliderBackgroundRectangle (int x, int y, int width, int height, float scale = 1.0f);
    /**Draws stick elements of background **/
    void drawSticks(Graphics &g , int x, int y , int width, int height);
    
};
