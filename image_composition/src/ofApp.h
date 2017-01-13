#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "image_document_list.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	void processOpenFileSelection(ofFileDialogResult openFileResult);

private:
	ImageDocumentList documentList;
	ofEasyCam cam;
	
	ofxGuiGroup arithmeticGui;
	ofParameter<bool> arithmeticAdd;
	ofParameter<bool> arithmeticSubtract;
	ofParameter<bool> arithmeticAlphaBlending;
	ofxFloatSlider arithmeticAlpha;
	ofParameter<bool> arithmeticRampImage;
	ofxIntSlider arithmeticRampStart;
	ofxIntSlider arithmeticRampEnd;

	ArithmeticParams arithmeticParams;

	void resetArithmetics();
	void arithmeticAddChanged(bool& show);
	void arithmeticSubtractChanged(bool& show);
	void arithmeticAlphaBlendingChanged(bool& show);
	void arithmeticRampImageChanged(bool& show);
	void arithmeticRampStartChanged(int& value);
	void arithmeticRampEndChanged(int& value);
	
	ofxPanel gui;

	int lastX;
	int lastY;

	void updateParameters();
};
