#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// load fonts
	fontSmall.load("D:/PERSO/Fonts/overpass-mono/overpass-mono-regular.otf", 10);
	fontLarge.load("D:/PERSO/Fonts/overpass-mono/overpass-mono-regular.otf", 12);
	fontXLarge.load("D:/PERSO/Fonts/overpass-mono/overpass-mono-regular.otf", 14);

	// colors
	bgColor = ofColor(237, 240, 239);
	txtColor = ofColor(52, 43, 50);
	itemColor = ofColor(252, 252, 252);

	// setting up GUI variables
	rotationSpeed.setup(0.0, ofColor(150, 150, 150), txtColor);
	rotationToggle.setup(false, txtColor);
	animationButton.setup("BOUNCE!", fontSmall, txtColor, itemColor);
	name.setup("Cube name", 20, fontSmall, txtColor, itemColor);
	// dropdown
	colorList.push_back("Red");
	colorList.push_back("Green");
	colorList.push_back("Blue");
	currIndInDropDown = 0;
	colorDropDown.setup(colorList, currIndInDropDown, fontSmall, txtColor, itemColor);

	// utils
	screen = ofVec2f(ofGetWidth(), ofGetHeight());
	center = screen / 2;

	// square
	sz = 200;
	sqColor = getColorFromDropDown(currIndInDropDown);
}

//--------------------------------------------------------------
void ofApp::update() {
	//
	if (animationButton.getValue() && anim >= 1.0) {
		anim = 0.0;
	}

	if (anim < 1.0) {
		szOffset = ofMapSin(anim, 0.0, 1.0, 100);
	}

	anim += 0.05;

	// update drop down and create event listener
	if (colorDropDown.getValueInt() != currIndInDropDown) {
		ofLog() << "Value of drop down menu changed to :\t" << colorList[colorDropDown.getValueInt()];
		sqColor = getColorFromDropDown(colorDropDown.getValueInt());
	}
	currIndInDropDown = colorDropDown.getValueInt();

	// square
	rotSpeed = ofMap(rotationSpeed.getValue(), 0.0, 1.0, 0.0, 2);

	if (rotationToggle.getValue())
		theta += rotSpeed;

	// utils
	mouse.set(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(bgColor);

	//// RECT
	// rectangle
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofTranslate(screen.x * 0.60, screen.y * 0.5);
	ofRotate(theta);

	// draw the cube
	ofSetColor(sqColor);
	ofFill();
	ofDrawRectangle(0, 0, sz + szOffset, sz + szOffset);

	// display its name
	ofRotate(-theta);
	ofSetColor(txtColor);
	string s = "This cube is called '" + name.getValue() + "'";
	fontLarge.drawString(s, -fontLarge.stringWidth(s) * 0.5, sz);

	ofPopMatrix();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CORNER);

	ofSetColor(txtColor);
	fontXLarge.drawString("ofxSimpleFloatingGui - example of use", 30, 30);
	ofDrawLine(30, 45, screen.x - 100, 45);


	//// GUI
	// create ofMatrix4x4 variable in which we will store future deformations
	ofMatrix4x4 transformMatrix;

	// translate to the center of application
	transformMatrix = ofMatrix4x4::newTranslationMatrix(ofVec3f(30, 90));

	ofPushMatrix();

	// apply transform
	ofMultMatrix(transformMatrix);

	// draw UI elements
	float xOffset = 0;
		// rotation toggle
	ofSetColor(txtColor);
	fontLarge.drawString("Rotation", 0, xOffset);
	rotationToggle.draw(0, xOffset+20, transformMatrix);
	xOffset += 80;
		// rotation speed
	ofSetColor(txtColor);
	fontLarge.drawString("Speed", 0, xOffset);
	rotationSpeed.draw(0, xOffset+20, transformMatrix);
	xOffset += 80;
		// launch animation
	ofSetColor(txtColor);
	fontLarge.drawString("Launch animation", 0, xOffset);
	animationButton.draw(0, xOffset+20, transformMatrix);
	xOffset += 100;
		// name
	ofSetColor(txtColor);
	fontLarge.drawString("Name the cube", 0, xOffset);
	name.draw(0, xOffset + 20, transformMatrix);
	xOffset += 100;
		// dropdown
	ofSetColor(txtColor);
	fontLarge.drawString("Select color", 0, xOffset);
	colorDropDown.draw(0, xOffset+20, transformMatrix);
	xOffset += 100;

	ofPopMatrix();
	//// END GUI
}

ofColor ofApp::getColorFromDropDown(int ind) {
	if (ind == 0) {				// red
		return ofColor(148, 25, 25);
	}
	else if (ind == 1) {		// green
		return ofColor(14, 156, 87);
	}
	else if (ind == 2) {		// blue
		return ofColor(20, 83, 110);
	}
	return ofColor::black;
}

float ofApp::ofMapSin(float x, float x1, float x2, float ytop) {
	float a = ytop * 0.5;
	float b = 2 * PI / (x2 - x1);
	float c = PI * (x2 - 3 * x1) / (x2 - x1);
	return a * cos(b * x + c) + a;
}
