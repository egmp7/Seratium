/*
  ==============================================================================

    SliderModel.h
    Created: 10 Feb 2023 6:49:27pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#pragma once

class SliderModel {
    
    
public:
    SliderModel(int _x,
                int _y,
                int _width,
                int _height,
                float _value);
    
    int x;
    int y;
    int width;
    int height;
    float value;
    
};
