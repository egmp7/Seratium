/*
  ==============================================================================

    DeckAnimation.h
    Created: 2 Feb 2023 7:28:48pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#pragma once

using namespace juce;
using namespace std;

class DeckAnimation : public AnimatedAppComponent
                      
{
public:
    DeckAnimation(DJAudioPlayer* _player);
    ~DeckAnimation() override;
    
    void paint (Graphics& g) override;
    /**Virtual function**/
    void update () override;
    /**Stores locally the DJAudioPlayer position*/
    void setPosition(float pos);
    
private:
    
    DJAudioPlayer* player;
    float position;
    
    /**creates an animation for the  x coordenate
     @param radius float
     @param offset float*/
    float animateX (float radius, int offset);
    /**creates an animation for the  y coordenate
     @param radius float
     @param offset float*/
    float animateY (float radius, int offset);
    
    
};
