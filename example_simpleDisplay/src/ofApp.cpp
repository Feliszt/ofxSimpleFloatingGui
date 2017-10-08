#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // load fonts
    font1.load("overpass-mono/overpass-mono-regular.otf", 10);
    font2.load("overpass-mono/overpass-mono-regular.otf", 12);

    // setting up GUI variables
    sliderTypeA.setup(300, 1200, 450, font1);
    sliderTypeB.setup();
    textField.setup("Text field", 10, font1);
    toggleButton.setup();
    button.setup();
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
        font2.drawString("SliderA", 0, 0);
        sliderTypeA.draw(0, 20, transformMatrix);
            // slider B
        font2.drawString("SliderB", 150, 0);
        sliderTypeB.draw(150, 20, transformMatrix);
            // text field
        font2.drawString("TextField", 300, 0);
        textField.draw(300, 20, transformMatrix);
            // toggle button
        font2.drawString("Toggle", 450, 0);
        toggleButton.draw(450, 20, transformMatrix);        
            // button
        font2.drawString("Button", 600, 0);
        button.draw(600, 20, transformMatrix);

    ofPopMatrix();
}
