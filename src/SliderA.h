#ifndef SliderA_H
#define SliderA_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ofMain.h"
#include "ofTrueTypeFont.h"

class SliderA
{
public:
    void setup(float _minValue, float _maxValue, float _value, ofTrueTypeFont _font, ofColor _textColor, ofColor _dragColor);
    float draw(float posX, float posY, ofMatrix4x4 transMatrix);
    float getValue();
    float getMinValue();
    float getMaxValue();

    SliderA();

private:
    // variables
    float   value;
    float   minValue;
    float   maxValue;
    ofVec2f posCenterString;
    ofVec2f mousePosStart;
    string  valueString;
    int     numDigit;
    int     numDigitPrev;
    float   valueStart;
    float   diff;
    bool hovered;
    bool dragged;
    bool draggedPrev;
    ofTrueTypeFont textFont;
    bool mousePressedPrev;
    ofColor textColor;
    ofColor hoverColor;
    ofColor dragColor;
    ofColor dragColorBoundary;

    ofVec2f getCenterOfString(string text);
};

#endif // SliderA_H
