#pragma once

#include "ofMain.h"
#include "ofxSimpleFloatingGui.h"

class ofApp: public ofBaseApp{
	public:
		void setup();
		void update();
        void draw();

        // GUI variables
        SliderA     sliderTypeA;
        SliderB     sliderTypeB;
        TextField   textField;
        Toggle      toggleButton;

        // font variables
        ofTrueTypeFont font1, font2;
};
