#include "SliderB.h"

SliderB::SliderB()
{

}

/// setup methods
void SliderB::setup()
{
    setup(0.0f);
}

void SliderB::setup(float _value)
{
    setup(_value, 100, 5, 7);
}

void SliderB::setup(float _value, int _wSlider, int _hSlider, int _rSlider)
{
    setup(_value, _wSlider, _hSlider, _rSlider, ofColor::gray, ofColor::black);
}

void SliderB::setup(float _value, ofColor _rectColor, ofColor _ellColor)
{
    setup(_value, 100, 5, 7, _rectColor, _ellColor);
}

void SliderB::setup(float _value, int _wSlider, ofColor _rectColor, ofColor _ellColor)
{
    setup(_value, _wSlider, 5, 7, _rectColor, _ellColor);
}

void SliderB::setup(float _value, int _wSlider, int _hSlider, int _rSlider, ofColor _rectColor, ofColor _ellColor)
{
    value = _value;
    rectColor = _rectColor;
    ellColor = _ellColor;

    wSlider = _wSlider;
    hSlider = _hSlider;
    rSlider = _rSlider;
}

/// draw method
float SliderB::draw(float posX, float posY, ofMatrix4x4 transMatrix){
    // debug
    //ofFill();
    //ofDrawCircle(posX, posY, 2);

    // compute position of slider
    ofPoint posRectAbs = ofPoint(posX, posY) * transMatrix;
    ofPoint posSlider = ofPoint(posX + value * wSlider, posY + hSlider / 2);
    ofPoint posSliderAbs = posSlider * transMatrix;

    // check if hovered
    ellHovered = (ofGetMouseX() < posSliderAbs.x + rSlider) &&
              (ofGetMouseX() > posSliderAbs.x - rSlider) &&
              (ofGetMouseY() < posSliderAbs.y + rSlider) &&
              (ofGetMouseY() > posSliderAbs.y - rSlider);

    rectHovered = (ofGetMouseX() < posRectAbs.x + wSlider)     &&
              (ofGetMouseX() > posRectAbs.x)                &&
              (ofGetMouseY() < posRectAbs.y + hSlider + 5)     &&
              (ofGetMouseY() > posRectAbs.y - 5);

    // check if ellipse is clicked on
    if(ellHovered && ofGetMousePressed() && !mousePressedPrev)
    {
        dragged = true;
        rectHovered = false;
    }

    // check if slider rectangle is clicked on
    if(rectHovered && ofGetMousePressed() && !mousePressedPrev)
    {
        // get where the slider is clicked on
        diff = ofGetMouseX() - posSliderAbs.x;

        // update value
        float valueUpdate = value + diff / wSlider;
        value = ofClamp(valueUpdate, 0, 1);
        dragged = true;
    }

    // this registers when we unclick
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
        float valueUpdate = valueStart + diff / wSlider;
        value = ofClamp(valueUpdate, 0, 1);
    }

    // set style
    ofPushStyle();

        ofFill();

        // draw slider
        ofSetColor(ellColor);
        ofDrawRectRounded(posX, posY, posSlider.x - posX, hSlider, 10);
        ofSetColor(rectColor);
        ofDrawRectRounded(posSlider.x, posY, wSlider - (posSlider.x - posX), hSlider, 10);

        // draw ellipse
        ofSetColor(ellColor);
        ofDrawCircle(posSlider, rSlider);

    // reset style
    ofPopStyle();

    // update stuff
    draggedPrev = dragged;
    mousePressedPrev = ofGetMousePressed();

    // return value
    return value;
}

/// getter for value
float SliderB::getValue(){
    return value;
}
