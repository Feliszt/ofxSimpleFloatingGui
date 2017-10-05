#ifndef SliderB_H
#define SliderB_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ofMain.h"

class SliderB
{
public:
    // methods
        // setup
    void setup();
    void setup(float _value);
    void setup(float _value, int _wSlider, int _hSlider, int _rSlider);
    void setup(float _value, ofColor _rectColor, ofColor _ellColor);
    void setup(float _value, int _wSlider, ofColor _rectColor, ofColor _ellColor);
    void setup(float _value, int _wSlider, int _hSlider, int _rSlider, ofColor _rectColor, ofColor _ellColor);
        // draw
    float draw(float posX, float poxY, ofMatrix4x4 transMatrix);
        // getter
    float getValue();

    SliderB();

private:
    float value;
    ofColor rectColor;
    ofColor ellColor;
    ofColor ellColorHovered;
    int     wSlider;
    int     hSlider;
    int     rSlider;
    bool    rectHovered;
    bool    ellHovered;
    bool    dragged;
    bool    draggedPrev;
    float   valueStart;
    ofVec2f mousePosStart;
    float   diff;
    bool    mousePressedPrev;
};

#endif // SliderB_H
