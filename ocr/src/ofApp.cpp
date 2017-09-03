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


int little_endian(int big) {
    int little = 0;
    
    return little;
}

int big_endian(int little) {
    int big = 0;
    
    big |= (little & 0xFF000000) >> 24;
    big |= (little & 0x00FF0000) >> 8;
    big |= (little & 0x0000FF00) << 8;
    big |= (little & 0x000000FF) << 24;
    
    return big;
}

bool ofApp::load_mnist(const std::string &path,
                       const std::string &kind,
                       std::vector<std::pair<ofImage, unsigned char>> *images)
{
    std::string label_path = path + kind + "-labels.idx1-ubyte";
    std::string images_path = path + kind + "-images.idx3-ubyte";
    
    FILE* lbpath = fopen(label_path.c_str(), "rb");
    if (lbpath == nullptr)
        return false;
    
    int magic, n;
    fread(&magic, sizeof(int), 1, lbpath);
    fread(&n,     sizeof(int), 1, lbpath);

    magic = big_endian(magic);
    n     = big_endian(n);
    
    unsigned char *labels = new unsigned char[n];
    fread(labels, sizeof(unsigned char), n, lbpath);
    fclose(lbpath);

    FILE* imgpath = fopen(images_path.c_str(), "rb");
    if (imgpath == nullptr)
        return false;

    int rows, cols;
    fread(&magic, sizeof(int), 1, imgpath);
    fread(&n,     sizeof(int), 1, imgpath);
    fread(&rows,  sizeof(int), 1, imgpath);
    fread(&cols,  sizeof(int), 1, imgpath);
    
    magic = big_endian(magic);
    n     = big_endian(n);
    rows  = big_endian(rows);
    cols  = big_endian(cols);
    
    int size = rows * cols;
    
    unsigned char* buf = new unsigned char[size];
    for (int i = 0; i < n; i++) {
        fread(buf, sizeof(unsigned char), size, imgpath);
        
        ofImage image;
        //image.allocate(cols, rows, ofImageType::OF_IMAGE_GRAYSCALE);
        image.setFromPixels(buf, cols, rows, ofImageType::OF_IMAGE_GRAYSCALE);
        
        images->push_back(std::make_pair(image, labels[i]));
    }
    
    fclose(imgpath);
    
    delete[] labels;
    delete[] buf;
    return true;
}


//--------------------------------------------------------------
void ofApp::setup(){
    std::string path = "/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/mnist/";
    load_mnist(path, "train", &train_images_);
    load_mnist(path, "t10k",  &t10k_images_);
    
    // Train the brain
    the_brain_.Initialize(4, 3, 3);
    the_brain_.SetLearningRate(0.2);
    the_brain_.SetMomentum(true, 0.9);
    
    int i;
    double error = 1.0;
    int c = 0;
    
    the_brain_.DumpData("/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PreTraining.txt");
    
    while (error > 0.05f && c < 50000) {
        error = 0;
        c++;
        
        for (i = 0; i < 14; i++) {
            the_brain_.SetInput(0, TrainingSet[i][0]);
            the_brain_.SetInput(1, TrainingSet[i][1]);
            the_brain_.SetInput(2, TrainingSet[i][2]);
            the_brain_.SetInput(3, TrainingSet[i][3]);
            
            the_brain_.SetDesiredOutput(0, TrainingSet[i][4]);
            the_brain_.SetDesiredOutput(1, TrainingSet[i][5]);
            the_brain_.SetDesiredOutput(2, TrainingSet[i][6]);
            
            the_brain_.FeedForward();
            error += the_brain_.CaluculateError();
            the_brain_.BackPropagate();
        }
        
        error /= 14.0;
    }
    
    the_brain_.DumpData("/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PostTraining.txt");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    const int canvas_cols = 32;
    const int canvas_rows = 32;
    const int n = canvas_rows * canvas_cols;
    
    for (int i = 0; i < n; i++) {
        ofImage image = train_images_[i].first;
        int label     = train_images_[i].second;
        
        ofPoint pt;
        int w = image.getWidth();
        int h = image.getHeight();
        
        pt.x = i % canvas_cols * w;
        pt.y = i / canvas_rows * h;
        
        ofSetColor(255, 255, 255);
        image.draw(pt, w, h);
        
        std::stringstream label_string;
        label_string << label;
        
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(label_string.str(), pt.x + w / 2, pt.y + h);
    }
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
