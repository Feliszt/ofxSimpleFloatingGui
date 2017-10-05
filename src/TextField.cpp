#include "TextField.h"

TextField::TextField()
{

}

void TextField::setup(string _displayedString, ofTrueTypeFont _stringFont, ofColor _stringColor)
{
    ofAddListener(ofEvents().keyPressed, this, &TextField::keyPressed);

    displayedString = _displayedString;
    stringFont = _stringFont;
    stringColor = _stringColor;

    bbPad = 3;
    blinkThresh = (int) (ofGetFrameRate() * 0.6);   // we want the blink to be 0.6 seconds long
}

string TextField::draw(float posX, float posY, ofMatrix4x4 transMatrix)
{
    // debug
    //ofFill();
    //ofDrawCircle(posX, posY, 2);

    // get bounding box of displayed string
    ofRectangle boundingBoxString;
    if(editMode){
        boundingBoxString = stringFont.getStringBoundingBox(editString, posX, posY);
    } else {
        boundingBoxString = stringFont.getStringBoundingBox(displayedString, posX, posY);
    }

    // set hover rectangle
    ofPoint     hoverRectPos = ofPoint(boundingBoxString.x - bbPad, boundingBoxString.y - bbPad);
    float       hoverRectW = boundingBoxString.width + bbPad * 2;
    float       hoverRectH = boundingBoxString.height + bbPad * 2;
    ofRectangle hoverRect = ofRectangle(hoverRectPos, hoverRectW, hoverRectH);

    // get absolute position of hover rectangle
    ofPoint     hoverRectPosAbs = hoverRectPos * transMatrix;

    // check if string is hovered
    hovered = (ofGetMouseX() < hoverRectPosAbs.x + hoverRectW) &&
              (ofGetMouseX() > hoverRectPosAbs.x)              &&
              (ofGetMouseY() < hoverRectPosAbs.y + hoverRectH) &&
              (ofGetMouseY() > hoverRectPosAbs.y);

    // if we click while hovered we enter edit mode
    if(ofGetMousePressed() && !mousePressedPrev)
    {
        editMode = hovered;
    }

    // if we just entered edit mode
    if(editMode && !editModePrev)
    {
        editString = displayedString;
        blinkTime = 0;
        blink = true;
    }

    // if we just quit edit mode
    if(!editMode && editModePrev)
    {
        // we save change into displayedString
        displayedString = editString;
    }

    ofPushStyle();

        // draw line under string if hovered
        if(hovered && !editMode) {
            ofSetLineWidth(2);
            ofSetColor(ofColor::black);
            ofDrawLine(hoverRect.getBottomLeft(), hoverRect.getBottomRight());
        }

        // draw blinking cursos if edit mode
        if(editMode)
        {
            // handle blinking
            blinkTime++;
            if(blinkTime >= blinkThresh) {
                blink = !blink;
                blinkTime = 0;
            }

            // draw line
            if(blink){
                ofSetLineWidth(2);
                ofSetColor(ofColor::black);
                ofDrawLine(hoverRect.getTopRight(), hoverRect.getBottomRight());
            }
        }

        // draw text inside
        ofSetColor(stringColor);
        if(editMode)
        {
            stringFont.drawString(editString, posX, posY);
        } else {
            stringFont.drawString(displayedString, posX, posY);
        }

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

void TextField::keyPressed(ofKeyEventArgs& eventArgs) {
    // debug
    //ofLog() << eventArgs.key;

    if(editMode) {
        // delete if backspace
        if(eventArgs.key == 8) {
            // remove last char
            if(editString.size() > 0) {
                editString = editString.substr(0, editString.size()-1);
            }
        }

        // only consider a-z or 0-9 or spacebar
        if((eventArgs.key >= 97 && eventArgs.key <= 122) || (eventArgs.key >= 48 && eventArgs.key <= 57) || eventArgs.key == 32) {
            editString += ofToString((char) eventArgs.key);
        }

        // if enter, exit edit mode
        if(eventArgs.key == 13){
            editMode = !editMode;
        }
    }
}
