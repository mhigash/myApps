#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "mnist_test.hpp"

typedef std::vector<std::pair<ofImage, unsigned char>> ImageLabelList;

class ofApp : public ofBaseApp{

    MnistTest mnist_;
    
	ofxGuiGroup type_gui_;
	ofParameter<bool> type_train_;
	ofParameter<bool> type_t10k_;

    ofxPanel gui;

	void ResetTypes();
	void TypeTrainChanged(bool& show);
	void TypeT10kChanged(bool& show);

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
