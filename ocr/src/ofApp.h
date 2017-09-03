#pragma once

#include "ofMain.h"
#include "neural_network.hpp"

class ofApp : public ofBaseApp{

    bool load_mnist(const std::string &path,
                    const std::string &kind,
                    std::vector<std::pair<ofImage, unsigned char>> *images);
    
    std::vector<std::pair<ofImage, unsigned char>> train_images_;
    std::vector<std::pair<ofImage, unsigned char>> t10k_images_;
    
    NeuralNetwork the_brain_;
    
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
