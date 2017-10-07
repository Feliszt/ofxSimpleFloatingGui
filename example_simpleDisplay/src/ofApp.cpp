#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // load fonts
    font1.load("overpass-mono/overpass-mono-regular", 11);
    font2.load("overpass-mono/overpass-mono-regular", 11);

    // setting up GUI variables
    sliderTypeA.setup(300, 800, 450, font1,ofColor::black, ofColor::blue);
    sliderTypeB.setup(0.5, 100, ofColor::gray, ofColor::black);
    textField.setup("A", 5, font1, ofColor::black);
    toggleButton.setup(true, ofColor::darkBlue);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // create ofMatrix4x4 variable in which we will store future deformations
    ofMatrix4x4 transformMatrix;

    // translate to the center of application
    transformMatrix = ofMatrix4x4::newTranslationMatrix(ofVec3f(30, 30));

    ofPushMatrix();

        // apply transform
        ofMultMatrix(transformMatrix);

        // draw UI elements
            // slider A
        ofSetColor(ofColor::black);
        font2.drawString("Slider showing value", 0, 0);
        sliderTypeA.draw(10, 20, transformMatrix);
            // slider B
        font2.drawString("Minimal slider with [0 - 1] range", 0, 70);
        sliderTypeB.draw(10, 90, transformMatrix);
            // text field
        font2.drawString("Text input box", 0, 140);
        textField.draw(10, 160, transformMatrix);
            // toggle button
        font2.drawString("Toggle button", 0, 210);
        toggleButton.draw(10, 230, transformMatrix);

    ofPopMatrix();
}
