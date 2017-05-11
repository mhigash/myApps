#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include <opencv2/opencv.hpp>
#include "util.hpp"
#include "classifier.h"

class ofApp : public ofBaseApp{
    
    typedef enum {
        kKnn,
        kBayes,
        kSvm,
        kPerceptron,
        kUnknown
    } Classifiers;
    
    ofxPanel gui;
    ofxGuiGroup classifierGroup;
    ofParameter<bool> classifierKnn;
    ofParameter<bool> classifierBayes;
    ofParameter<bool> classifierSvm;
    ofParameter<bool> classifierPerceptron;
    
    ofxGuiGroup runGroup;
    ofxButton trainingButton;
    ofxButton classifyButton;
    
  
    
    Classifiers classifier_type_;

    cv::Mat image_;
    cv::Mat data_;
    cv::Mat label_;
    cv::Point2f min_;
    cv::Point2f max_;
    
    Classifier* classifier_;
    cv::Mat classified_label_;

    // mesh grid for classification
    cv::Mat label_map_;
    cv::Mat label_map_resized_;
    
    // arguments for findContours
    vector<vector<cv::Point> > contours_;
    vector<cv::Vec4i> hierarchy_;

    // histroy of operation
    std::vector<std::string> history_;

    bool LoadData(const std::string& filepath);
    void ClassifyData();
    void UpdateContours(int width, int height);
    
    void SetClassifierType(Classifiers classifier);
    void AddHistory(bool training, float elapsed);
    
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
    
    void classifierKnnChanged(bool& show);
    void classifierBayesChanged(bool& show);
    void classifierSvmChanged(bool& show);
    void classifierPerceptronChanged(bool& show);
    void trainingButtonPressed();
    void classifyButtonPressed();
    
};
