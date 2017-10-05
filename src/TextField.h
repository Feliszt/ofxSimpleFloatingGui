#ifndef TextField_H
#define TextField_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ofMain.h"
#include "ofTrueTypeFont.h"

class TextField
{
public:
    // methods
    void setup(string _displayedString, ofTrueTypeFont _stringFont, ofColor _stringColor);
    string draw(float posX, float posY, ofMatrix4x4 transMatrix);
    string getValue();

    TextField();

private:
    // methods
    void keyPressed(ofKeyEventArgs& eventArgs);

    // variables
    string          displayedString;
    string          editString;
    ofTrueTypeFont  stringFont;
    ofColor         stringColor;
    int             bbPad;
    bool            hovered;
    bool            editMode;
    bool            editModePrev;
    bool            mousePressedPrev;
    int             blinkTime;
    bool            blink;
    int             blinkThresh;
};

#endif // TextField_H
