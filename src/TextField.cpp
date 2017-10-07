#include "TextField.h"

TextField::TextField()
{

}

void TextField::setup(string _displayedString, int _maxChar, ofTrueTypeFont _stringFont, ofColor _stringColor)
{
    ofAddListener(ofEvents().keyPressed, this, &TextField::keyPressed);

    displayedString = _displayedString;
    stringFont = _stringFont;
    stringColor = _stringColor;
    maxChar = _maxChar;

    // set up background rectangle size
    padX = 15;
    padY = 8;
    lineHeight = stringFont.getLineHeight();
    float rectW = stringFont.stringWidth(_displayedString) + 2 * padX;
    float rectH = lineHeight + 2 * padY;

    // init other variables
    maxSize = getMaxSize(_stringFont, _maxChar) + 2 * padX;
    backgroundRect = ofRectangle(0, 0, rectW, rectH);
    nChar = displayedString.size();
    backgroundColor.set(230);
    blinkThresh = (int) (ofGetFrameRate() * 0.6);   // we want the blink to be 0.6 seconds long
}

string TextField::draw(float posX, float posY, ofMatrix4x4 transMatrix)
{
    // debug
    //ofFill();
    //ofDrawCircle(posX, posY, 2);

    // get absolute position of hover rectangle
    ofPoint     backgroundRectPosAbs = ofPoint(posX, posY) * transMatrix;

    // check if string is hovered
    hovered = (ofGetMouseX() < backgroundRectPosAbs.x + backgroundRect.width)  &&
              (ofGetMouseX() > backgroundRectPosAbs.x)                         &&
              (ofGetMouseY() < backgroundRectPosAbs.y + backgroundRect.height) &&
              (ofGetMouseY() > backgroundRectPosAbs.y);

    // if we click while hovered we enter edit mode
    if(ofGetMousePressed() && !mousePressedPrev)
    {
        editMode = hovered;
    }

    // if we just entered edit mode
    if(editMode && !editModePrev)
    {
        editString = displayedString;
        backgroundRect.setWidth(maxSize);
        blinkTime = 0;
        blink = true;
    }

    // if we just quit edit mode
    if(!editMode && editModePrev)
    {
        // we save change into displayedString
        displayedString = editString;
        backgroundRect.setWidth(stringFont.stringWidth(editString) + 2 * padX);
    }

    // if we are currently in edit mode
    if(editMode)
    {
        // get string rect
        cursorX = stringFont.stringWidth(editString);

        // handle blinking
        blinkTime++;
        if(blinkTime >= blinkThresh) {
            blink = !blink;
            blinkTime = 0;
        }
    }

    ofPushStyle();
    ofSetLineWidth(1);

        ofPushMatrix();
        ofTranslate(posX, posY);

            // draw background rectangle
            ofSetColor(backgroundColor);
            ofDrawRectRounded(backgroundRect, backgroundRect.height / 10);
            ofNoFill();
            ofSetColor((hovered && !editMode) ? ofColor::gray : ofColor::black);
            ofDrawRectRounded(backgroundRect, backgroundRect.height / 10);

            // draw string
            ofSetColor(stringColor);
            stringFont.drawString(editMode ? editString : displayedString, padX, padY + lineHeight);

            // draw line
            if(editMode && blink){
                ofSetLineWidth(2);
                ofSetColor(ofColor::black);
                ofDrawLine(cursorX + padX + 3, padY, cursorX + padX + 3, padY + lineHeight + 3);
            }

            /*
            // debug stuff
            ofNoFill();
            ofSetLineWidth(1);
            ofSetColor(ofColor::black);
            ofDrawRectangle(padX, padY, stringFont.stringWidth(editMode ? editString : displayedString), stringFont.getLineHeight());

            ofSetColor(ofColor::black);
            ofDrawLine(0, rectH / 2, rectW, rectH / 2);
            ofDrawLine(rectW / 2, 0, rectW / 2, rectH);
            */

        ofPopMatrix();
    ofPopStyle();

    // update states
    mousePressedPrev    = ofGetMousePressed();
    editModePrev        = editMode;

    // we return displayedString, this means that this value changed when we leave edit mode
    return displayedString;
}

// getter
string TextField::getValue(){
    return displayedString;
}


float TextField::getMaxSize(ofTrueTypeFont _font, int _sz) {
    std::stringstream ss;
    for(int i = 0; i < _sz; i++) {
        ss << 'A';
    }
    return _font.stringWidth(ss.str());
}

void TextField::keyPressed(ofKeyEventArgs& eventArgs) {
    // debug
    //ofLog() << eventArgs.key;

    if(editMode) {
        // delete if backspace
        if(eventArgs.key == 8) {
            // remove last char
            if(editString.size() > 0) {
                editString = editString.substr(0, editString.size()-1);
                nChar -= 1;
            }
        }

        // only consider a-z or 0-9 or spacebar
        if((nChar < maxChar) && ((eventArgs.key >= 97 && eventArgs.key <= 122) || (eventArgs.key >= 48 && eventArgs.key <= 57) || eventArgs.key == 32)) {
            editString += ofToString((char) eventArgs.key);
            nChar += 1;
        }

        // if enter, exit edit mode
        if(eventArgs.key == 13){
            editMode = !editMode;
        }
    }
}
