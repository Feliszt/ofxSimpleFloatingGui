#pragma once

#include "ofMain.h"
#include "ofxSimpleFloatingGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	ofColor getColorFromDropDown(int ind);
	float ofMapSin(float x, float x1, float x2, float ytop);

	// GUI variables
	SliderB     rotationSpeed;
	Toggle      rotationToggle;
	Button      animationButton;
	DropDown	colorDropDown;
	vector<string> colorList;
	int			currIndInDropDown;
	TextField   name;

	// font variables
	ofTrueTypeFont fontSmall, fontLarge, fontXLarge;

	// colors
	ofColor txtColor, bgColor, itemColor;

	// utils
	ofVec2f screen, center, mouse;

	// square
	float theta = 0.0;					// rotation
	float rotSpeed;						// speed
	float sz, szOffset;							// size
	ofColor sqColor;					// square color
	float anim = 1.0;
};
