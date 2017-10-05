#ifndef TOGGLE_H
#define TOGGLE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ofMain.h"

class Toggle
{
public:
    // methods
        // setup
    void setup();
    void setup(bool _value);
    void setup(bool _value, ofColor _trueColor);
        // draw
    bool draw(float posX, float poxY, ofMatrix4x4 transMatrix);
        // getters
    bool getValue();

    Toggle();
private:
    // variables
    bool    value;
        // design
    ofColor trueColor;
    ofColor falseColor;
    int     circlePad;
    int     rectW;
    int     rectH;
        // states
    bool    hovered;
    bool    clicked;
    bool    mousePressedPrev;
        // toggle animation
    float     animCounter;
    int     animTime;
    float   deltaT;
    bool    animRunningUP;
    bool    animRunningDOWN;
};

#endif // TOGGLE_H
