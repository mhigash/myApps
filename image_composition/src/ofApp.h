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
	
	ofxGuiGroup blendingGui;
	ofParameter<bool> blendingAdd;
	ofParameter<bool> blendingSubtract;
	ofParameter<bool> blendingAlphaBlending;
	ofxFloatSlider blendingAlpha;
	ofParameter<bool> blendingRampImage;
	ofxIntSlider blendingRampStart;
	ofxIntSlider blendingRampEnd;

	BlendingParams blendingParams;

	void resetBlendings();
	void blendingAddChanged(bool& show);
	void blendingSubtractChanged(bool& show);
	void blendingAlphaBlendingChanged(bool& show);
	void blendingRampImageChanged(bool& show);
	void blendingRampStartChanged(int& value);
	void blendingRampEndChanged(int& value);
	
	ofxPanel gui;

	int lastX;
	int lastY;

	void updateParameters();
};
