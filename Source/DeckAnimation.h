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
    DeckAnimation(DJAudioPlayer*);
    ~DeckAnimation() override;
    
    void paint (Graphics& g) override;
    /**Checks the position of the player to animate the dj plate */
    void update () override;
    
private:

    /**Algorithm to produce an ellipse in the x coordenate
     @param radius size of the ellipse
     @param offset add extra points to the ellipse, this is required for the Path class*/
    float animateX (float radius, int offset);
    /**Algorithm to produce an ellipse in the y coordenate
     @param radius size of the ellipse
     @param offset add extra points to the ellipse, this is required for the Path class*/
    float animateY (float radius, int offset);
    
    DJAudioPlayer* player;
    float position;
    
};
