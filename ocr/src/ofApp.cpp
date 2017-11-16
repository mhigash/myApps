#include <stdio.h>
#include <stdlib.h>

#include "ofApp.h"


double			TrainingSet[14][7] = {
    0,		1,		0,		0.2,	0.9,	0.1,	0.1,
    0,		1,		1,		0.2,	0.9,	0.1,	0.1,
    0,		1,		0,		0.8,	0.1,	0.1,	0.1,
    0.1,	0.5,	0,		0.2,	0.9,	0.1,	0.1,
    0,		0.25,	1,		0.5,	0.1,	0.9,	0.1,
    0,		0.2,	1,		0.2,	0.1,	0.1,	0.9,
    0.3,	0.2,	0,		0.2,	0.9,	0.1,	0.1,
    0,		0.2,	0,		0.3,	0.1,	0.9,	0.1,
    0,		1,		0,		0.2,	0.1,	0.9,	0.1,
    0,		1,		1,		0.6,	0.1,	0.1,	0.1,
    0,		1,		0,		0.8,	0.1,	0.9,	0.1,
    0.1,	0.2,	0,		0.2,	0.1,	0.1,	0.9,
    0,		0.25,	1,		0.5,	0.1,	0.1,	0.9,
    0,		0.6,	0,		0.2,	0.1,	0.1,	0.9
};


//--------------------------------------------------------------
void ofApp::setup() {

	gui.setup();

	type_gui_.setup();
	type_gui_.setName("type");
	type_gui_.add(type_train_.set("train", false, false, true));
	type_gui_.add(type_t10k_.set("t10k", false, false, true));

	type_train_.addListener(this, &ofApp::TypeTrainChanged);
	type_t10k_.addListener(this, &ofApp::TypeT10kChanged);
	ResetTypes();
	type_train_ = true;

	gui.add(&type_gui_);


	std::string path = "/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/mnist/";
	//std::string path = "D:\\Vi\\ViSample\\python_machine_learning\\";

	mnist_.LoadData(path);
    mnist_.Train();

	//train_the_brain();
    
    const int canvas_cols = 32;
    const int canvas_rows = 32;
    const int image_cols = 28;
    const int image_rows = 28;
    const int size = canvas_cols * canvas_rows * image_cols * image_rows;
    unsigned char* pixels = new unsigned char[size];
    
    ofImage image;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    const int canvas_cols = 32;
    const int canvas_rows = 32;
    const int n = canvas_rows * canvas_cols;

    std::string kind = kTrain;
	if (type_t10k_)
		kind = kT10k;

	if (mnist_.GetImageCount(kind) <= 0) return;

    for (int i = 0; i < n; i++) {
        ImageAndLabel image_and_label;
        mnist_.GetImage(kind, i, image_and_label);
        
        ofImage image;
        int rows = mnist_.GetImageHeight();
        int cols = mnist_.GetImageWidth();
        image.setFromPixels(image_and_label.first,
                            mnist_.GetImageWidth(),
                            mnist_.GetImageHeight(),
                            ofImageType::OF_IMAGE_GRAYSCALE);

        int label     = image_and_label.second;
        int w = image.getWidth();
        int h = image.getHeight();
        
		ofPoint pt;
		pt.x = i % canvas_cols * w;
        pt.y = i / canvas_rows * h;
        
        ofSetColor(255, 255, 255);
        image.draw(pt, w, h);
        
        std::stringstream label_string;
        label_string << label;
        
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(label_string.str(), pt.x + w / 2, pt.y + h);
    }

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::ResetTypes()
{
	type_train_.removeListener(this, &ofApp::TypeTrainChanged);
	type_t10k_.removeListener(this, &ofApp::TypeT10kChanged);
	type_train_ = false;
	type_t10k_ = false;
	type_train_.addListener(this, &ofApp::TypeTrainChanged);
	type_t10k_.addListener(this, &ofApp::TypeT10kChanged);
}

void ofApp::TypeTrainChanged(bool& show)
{
	ResetTypes();
	type_train_ = true;
}

void ofApp::TypeT10kChanged(bool& show)
{
	ResetTypes();
	type_t10k_ = true;
}

