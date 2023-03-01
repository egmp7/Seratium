/*
  ==============================================================================

    DeckAnimation.cpp
    Created: 2 Feb 2023 7:28:48pm
    Author:  Erick Gonzalez

  ==============================================================================
*/

#include "DeckAnimation.h"

DeckAnimation::DeckAnimation(DJAudioPlayer* _player)
:
player(_player),
position(0.0f)
{
    setFramesPerSecond (60); // Init Animation
}

DeckAnimation::~DeckAnimation()
{
    
}

void DeckAnimation::update ()
{
    float pos = player->getPosition();
    if(position != pos && !isnan(pos))
        position = pos;
}

void DeckAnimation::paint (Graphics& g)
{
    int size = min(getLocalBounds().getWidth(),getLocalBounds().getHeight());
    float responsiveSize = (float) size * 0.009f;
     
    g.fillAll(Colour(36, 17, 51));
    
    // bigger circle
    int d1 = 100 * responsiveSize;
    g.setColour(Colours::black);
    g.fillEllipse(getWidth()/2 - d1/2, getHeight()/2 -d1/2, d1, d1);
    
    // small circle
    int d2 = 40 * responsiveSize ;
    g.setColour(Colour(213,210,255));
    g.fillEllipse(getWidth()/2 - d2/2, getHeight()/2 -d2/2, d2, d2);
    
    // deck line animation
    int pointRadius1 = 50 * responsiveSize;
    int pointRadius2 = 20 * responsiveSize;
    
    Point<float> startPoint (animateX(pointRadius1 , 0), animateY(pointRadius1 , 0));
    Point<float> endPoint   (animateX(pointRadius2 , 0), animateY(pointRadius2 , 0));
    
    g.setColour (Colour(137,70,205));
    g.drawLine(Line<float>(startPoint, endPoint),3.0f);
     
    // ring deck animation
    
    int ringRadius = 50 * responsiveSize;
    auto numberOfDots = 62 ;
    Path path;

    // i = 2 to offset the start of the path
    for (auto i = 2; i < numberOfDots; ++i)
    {
        // get points
        Point<float> p (animateX(ringRadius, i),animateY(ringRadius, i));

        if (i == 2)     // start
            path.startNewSubPath (p);
        else            // add points to Path
            path.lineTo (p);
    }

    g.strokePath (path, PathStrokeType (3.0f));
    
}

float DeckAnimation::animateX (float radius, int offset)
{
    // math to animate a point or varius depending on offset
    return (float)getWidth()  / 2.0f + (float) radius * (-std::sin ((float) position * 1.5f + (float) offset * 0.10f));
}

float DeckAnimation::animateY (float radius, int offset)
{
    // math to animate a point or varius depending on offset
    return (float) getHeight() / 2.0f + (float) radius * std::cos ((float) position * 1.5f + (float) offset * 0.10f);
}



