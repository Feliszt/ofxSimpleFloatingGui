#include "SliderA.h"

SliderA::SliderA()
{

}

/// setup
void SliderA::setup(float _minValue, float _maxValue, float _value, ofTrueTypeFont _font, ofColor _textColor, ofColor _dragColor)
{
    minValue = _minValue;
    maxValue = _maxValue;
    value = _value;
    textFont = _font;
    textColor = _textColor;
    dragColor = _dragColor;
    dragColorBoundary = _dragColor;
    dragColorBoundary.setBrightness(100);

    posCenterString = getCenterOfString(ofToString(value));
}

/// draw
float SliderA::draw(float posX, float posY, ofMatrix4x4 transMatrix){
    // debug
    //ofFill();
    //ofDrawCircle(posX, posY, 2);

    // get absolute position of string
    ofPoint posStringAbs = ofPoint(posX + posCenterString.x, posY - posCenterString.y) * transMatrix;

    // get string from value
    valueString = ofToString((int) value);

    // check if hovered
    hovered = (ofGetMouseX() < posStringAbs.x + 40) &&
              (ofGetMouseX() > posStringAbs.x - 40) &&
              (ofGetMouseY() < posStringAbs.y + 10) &&
              (ofGetMouseY() > posStringAbs.y - 10);

    // check if dragged
    if(hovered && ofGetMousePressed() && !mousePressedPrev)
    {
        dragged = true;
    }
    dragged &= ofGetMousePressed();

    // store mouse posString and value when dragging starts
    if(dragged && !draggedPrev)
    {
        mousePosStart = ofVec2f(ofGetMouseX(), ofGetMouseY());
        valueStart = value;
    }

    // compare mouse posStringition to stored posStringition and update value accordingly
    if(dragged)
    {
        diff = ofGetMouseX() - mousePosStart.x;
        float valueUpdate = valueStart + diff / ofGetWidth() * (maxValue - minValue);
        value = ofClamp(valueUpdate, minValue, maxValue);
    }

    // get boundingbox of string
    numDigit = valueString.length();
    if(numDigit != numDigitPrev) posCenterString = getCenterOfString(valueString);

    // update stuff
    draggedPrev = dragged;
    mousePressedPrev = ofGetMousePressed();
    numDigitPrev = numDigit;

    // draw value
    ofSetColor(textColor);
    textFont.drawString(valueString, posX, posY);

    // translate
    ofPushStyle();
    ofFill();
    ofPushMatrix();
    ofTranslate(posX + posCenterString.x, posY - posCenterString.y, 0);

        if((hovered && !dragged) || (dragged && diff == 0))
        {
            ofSetColor(dragColor);
            ofDrawTriangle(20, - 5, 20, 5, 25, 0);
            ofDrawTriangle(- 20, -5, - 20, 5, - 25, 0);
        }

        if(dragged && (diff > 0))
        {
            ofSetColor(dragColor);
            if(value == maxValue)
            {
                ofSetColor(dragColorBoundary);

            }
            ofDrawTriangle(20, - 5, 20, 5, 25, 0);
        }

        if(dragged && (diff < 0))
        {
            ofSetColor(dragColor);
            if(value == minValue)
            {
                ofSetColor(dragColorBoundary);

            }
            ofDrawTriangle(- 20, -5, - 20, 5, - 25, 0);
        }

    ofPopMatrix();
    ofNoFill();
    ofPopStyle();

    // return value
    return value;
}

/// getter for value
float SliderA::getValue(){
    return value;
}

/// getter for max value
float SliderA::getMaxValue(){
    return maxValue;
}

/// getter for min value
float SliderA::getMinValue(){
    return minValue;
}


ofVec2f SliderA::getCenterOfString(string text)
{
    ofRectangle stringBoundingBox = textFont.getStringBoundingBox(text, 0, 0);
    return ofVec2f(stringBoundingBox.getWidth() / 2, stringBoundingBox.getHeight() / 2);
}
