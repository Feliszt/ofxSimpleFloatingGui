#include "Toggle.h"

Toggle::Toggle()
{

}

/// setup
void Toggle::setup(){
    setup(false);
}

void Toggle::setup(bool _value){
    setup(_value, ofColor::black);
}

void Toggle::setup(bool _value, ofColor _trueColor){
    value       = _value;
    trueColor   = _trueColor;

    falseColor = ofColor::gray;
    rectW = 15;
    rectH = 18;
    circlePad = 2;
    animTime = (int) (ofGetFrameRate() * 0.1); // it takes 0.5 seconds for the animation to play
    deltaT  = 1 / (float) animTime;
    animCounter = value;
}

/// draw
bool Toggle::draw(float posX, float posY, ofMatrix4x4 transMatrix){
    // debug
    //ofFill();
    //ofDrawCircle(posX, posY, 2);

    // get absolute position of button
    ofPoint posAbs = ofPoint(posX, posY) * transMatrix;

    // compute bounding box
    ofRectangle boundingBox = ofRectangle(posAbs, rectW + rectH, rectH);

    // check if hovered
    hovered = (ofGetMouseX() < boundingBox.getRight())     &&
              (ofGetMouseX() > boundingBox.getLeft())      &&
              (ofGetMouseY() < boundingBox.getBottom())    &&
              (ofGetMouseY() > boundingBox.getTop());

    // check if button is clicked on
    if(hovered && ofGetMousePressed() && !mousePressedPrev)
    {
        clicked = true;
        value = !value;

        // run animation
        if(value){
            animRunningUP = true;
        } else {
            animRunningDOWN = true;
        }
    }

    // update counter animation
    if(animRunningUP){
        animCounter += deltaT;
    }
    if(animRunningDOWN){
        animCounter -= deltaT;
    }
    if(animCounter >= 1){
        animRunningUP = false;
    }
    if(animCounter <= 0){
        animRunningDOWN = false;
    }

    // set attributes of button
    ofColor targetColor = falseColor;
    ofColor buttonColor = targetColor.lerp(trueColor, animCounter);
    float buttonPos = animCounter * rectW * sin(animCounter * PI / 2);

    // draw toggle
    ofPushMatrix();
    ofTranslate(posX + rectH /2, posY);

            // draw rect
        ofSetColor(buttonColor);
        ofDrawCircle(0, rectH / 2, rectH / 2);
        ofDrawRectangle(0, 0, rectW, rectH);
        ofDrawCircle(rectW, rectH / 2, rectH / 2);
            // draw circle
        ofSetColor(ofColor::white);
        ofDrawCircle(buttonPos, rectH /2, rectH / 2 - circlePad);

    ofPopMatrix();

    // update state
    mousePressedPrev = ofGetMousePressed();
}

/// getter
bool Toggle::getValue(){
    return value;
}
