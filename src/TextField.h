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
    void setup(string _displayedString, int _maxChar, ofTrueTypeFont _stringFont, ofColor _stringColor);
    string draw(float posX, float posY, ofMatrix4x4 transMatrix);
    string getValue();

    TextField();

private:
    // methods
    void keyPressed(ofKeyEventArgs& eventArgs);
    float getMaxSize(ofTrueTypeFont _font, int _sz);

    // variables
        // value
    string          displayedString;
    string          editString;
    int             maxChar;
    int             nChar;
        // design
    ofTrueTypeFont  stringFont;
    ofColor         stringColor;
    ofColor         backgroundColor;
    ofRectangle     backgroundRect;
    float           maxSize;
    int             padX, padY;
    float           cursorX;
    float           lineHeight;
    bool            hovered;
    bool            editMode;
    bool            editModePrev;
    bool            mousePressedPrev;
    int             blinkTime;
    bool            blink;
    int             blinkThresh;
};

#endif // TextField_H
