#include "ofApp.h"

#include "knn_classifier.hpp"
#include "bayes_classifier.hpp"
#include "svm_classifier.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetVerticalSync(true);
    gui.setup();
    
    classifierGroup.setup("classifier");
    classifierGroup.add(classifierKnn.set("knn", false, true, false));
    classifierGroup.add(classifierBayes.set("bayes", false, true, false));
    classifierGroup.add(classifierSvm.set("svm", false, true, false));
    classifierGroup.setName("classfier");
    
    runGroup.setup("run");
    runGroup.add(trainingButton.setup("training"));
    runGroup.add(classifyButton.setup("classify"));
    runGroup.setName("run");
    
    trainingButton.addListener(this, &ofApp::trainingButtonPressed);
    classifyButton.addListener(this, &ofApp::classifyButtonPressed);
    
    gui.add(&classifierGroup);
    gui.add(&runGroup);
    
    SetClassifier(kKnn);
    
    classifier_ = nullptr;
    
//    cv::Mat image = cv::imread("20161127-01.jpg");
//    
//    int cols = image.cols;
//
//    if (image.empty())
//        printf("empty");
    
//    std::vector<cv::Vec3f> pointList;
//    loadPoints3("/Users/hgsmrmss/Documents/code_samples/python/points.csv", pointList);
//    
//    cv::Vec3f point3 = pointList[0];
//    cout << point3;
    
    ofFill();

#if 0
    classifier_ = new SvmClassifier();
    
    for (int i = 0; i < 2; i++) {
        char filepath[256];
        sprintf(filepath, "/Users/hgsmrmss/Documents/code_samples/python/points_normal%d.csv", i);
//        sprintf(filepath, "/Users/hgsmrmss/Documents/code_samples/python/points_ring%d.csv", i);
        LoadCsvAsImage(filepath, '\t', image_);
        
        double min_val, max_val;
        cv::minMaxLoc(image_.col(0), &min_val, &max_val);
        min_.x = static_cast<float>(min_val);
        max_.x = static_cast<float>(max_val);
        cv::minMaxLoc(image_.col(1), &min_val, &max_val);
        min_.y = static_cast<float>(min_val);
        max_.y = static_cast<float>(max_val);
        
        data_ = cv::Mat(image_, cv::Rect(0, 0, image_.cols - 1, image_.rows));
        label_ = cv::Mat(image_, cv::Rect(image_.cols - 1, 0, 1, image_.rows));
        classified_label_ = cv::Mat::zeros(image_.rows, 1, CV_32F);
        
        cout << image_.size() << endl;
        cout << data_.size() << endl;
        cout << label_.size() << endl;
        
        if (i == 0) {
            classifier_->Train(data_, label_);
        }
    }
    
    ClassifyData();
#endif
    
}

bool ofApp::LoadData(const std::string& filepath) {
    
    LoadCsvAsImage(filepath, '\t', image_);
    
    double min_val, max_val;
    cv::minMaxLoc(image_.col(0), &min_val, &max_val);
    min_.x = static_cast<float>(min_val);
    max_.x = static_cast<float>(max_val);
    cv::minMaxLoc(image_.col(1), &min_val, &max_val);
    min_.y = static_cast<float>(min_val);
    max_.y = static_cast<float>(max_val);
    
    data_ = cv::Mat(image_, cv::Rect(0, 0, image_.cols - 1, image_.rows));
    label_ = cv::Mat(image_, cv::Rect(image_.cols - 1, 0, 1, image_.rows));
    classified_label_ = cv::Mat::zeros(image_.rows, 1, CV_32F);
    
    contours_.clear();
    hierarchy_.clear();
    
    cout << image_.size() << endl;
    cout << data_.size() << endl;
    cout << label_.size() << endl;
    
    return true;
}


//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::ClassifyData()
{
    if (!classifier_)
        return;
    
    float width = static_cast<float>(ofGetWidth());
    float height = static_cast<float>(ofGetHeight());
    
    for (int r = 0; r < data_.rows; r++) {
        classified_label_.at<float>(r, 0) = classifier_->Classify(data_.row(r));
    }
    
    cv::Size mesh_size(width / 10, height / 10);
    cv::Point2f step;
    step.x = (max_.x - min_.x) / mesh_size.width;
    step.y = (max_.y - min_.y) / mesh_size.height;
    label_map_ = cv::Mat(mesh_size.height, mesh_size.width, CV_32F);
    
    int row = 0;
    int col = 0;
    
    cv::Mat data(1, 2, CV_32F);

    for (float y = min_.y; y <= max_.y; y += step.y) {
        for (float x = min_.x; x <= max_.x; x += step.x) {
            
            data.at<float>(0, 0) = x;
            data.at<float>(0, 1) = y;
            
            float label = classifier_->Classify(data);
            label_map_.at<float>(row, col) = label;
            
            col++;
        }
        
        row++;
        col = 0;
    }
    
    UpdateContours(width, height);
}

void ofApp::UpdateContours(int width, int height) {
    //
    // for drawing classified data on the window,
    // classified label map is resize to fit size of window.
    //
    cv::resize(label_map_, label_map_resized_, cv::Size2i(width, height));
    
    //Extract contours from resize map
    vector<vector<cv::Point> > contours0;
    
    cv::Mat label_map2 = label_map_resized_ == 1.0f;
    
    // Finding contours on the image whose label is 1
    findContours(label_map2, contours0, hierarchy_, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    
    contours_.resize(contours0.size());
    for( size_t k = 0; k < contours0.size(); k++ )
        cv::approxPolyDP(cv::Mat(contours0[k]), contours_[k], 3, true);
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    float width = static_cast<float>(ofGetWidth());
    float height = static_cast<float>(ofGetHeight());
    
    float* p = reinterpret_cast<float*>(data_.data);
    for (int r = 0; r < data_.rows; r++) {
        float x = data_.row(r).at<float>(0, 0);
        float y = data_.row(r).at<float>(0, 1);
        
        x = (x - min_.x) / (max_.x - min_.x) * width;
        y = (y - min_.y) / (max_.y - min_.y) * height;
        
        float label = label_.at<float>(r, 0);
        float classified_label = classified_label_.at<float>(r, 0);
        
        if (label == classified_label) {
            //
            // data classified correctly labels are drawn as circle
            // label 1 is colored in red
            //
            if (label_.at<float>(r, 0) == 1.0f)
                ofSetColor(255, 0, 0);
            else
                ofSetColor(0, 0, 255);
            ofDrawCircle(x, y, 3.0f);
        } else {
            //
            // misclassified labels are drawn as square
            //
            if (label_.at<float>(r, 0) == 1.0f)
                ofSetColor(255, 0, 0);
            else
                ofSetColor(0, 0, 255);
            ofDrawRectangle(x - 2.0f, y - 2.0f, 5.0f, 5.0f);
        }
    }
    
    // drawing countours of classified mesh.
    ofSetColor(255, 0, 0);
    
    vector<vector<cv::Point> >::iterator itr1;
    vector<cv::Point>::iterator itr2;
    
    for (itr1 = contours_.begin(); itr1 != contours_.end(); itr1++) {
        ofPoint p0, p1, p2;
        for (itr2 = itr1->begin(); itr2 != itr1->end(); itr2++) {
            
            if (itr2 == itr1->begin()) {
                p1.x = itr2->x;
                p1.y = itr2->y;
                p0 = p1;
                continue;
            }
            
            p2.x = itr2->x;
            p2.y = itr2->y;
            
            ofDrawLine(p1, p2);
            
            p1 = p2;
        }
        ofDrawLine(p2, p0);
    }
 
    
    gui.setPosition(ofGetWidth() - gui.getWidth() - 10, gui.getPosition().y);
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
    UpdateContours(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::SetClassifier(Classifiers classifier) {
    classifierKnn.removeListener(this, &ofApp::classifierKnnChanged);
    classifierBayes.removeListener(this, &ofApp::classifierBayesChanged);
    classifierSvm.removeListener(this, &ofApp::classifierSvmChanged);
    
    classifierKnn = false;
    classifierBayes = false;
    classifierSvm = false;
    
    classifier_type_ = classifier;
    
    if (classifier_type_ == kKnn) {
        classifierKnn = true;
    } else if (classifier_type_ == kBayes) {
        classifierBayes = true;
    } else if (classifier_type_ == kSvm) {
        classifierSvm = true;
    }
    
    classifierKnn.addListener(this, &ofApp::classifierKnnChanged);
    classifierBayes.addListener(this, &ofApp::classifierBayesChanged);
    classifierSvm.addListener(this, &ofApp::classifierSvmChanged);
}

void ofApp::classifierKnnChanged(bool& show) {
    SetClassifier(kKnn);
}

void ofApp::classifierBayesChanged(bool& show) {
    SetClassifier(kBayes);
}

void ofApp::classifierSvmChanged(bool& show) {
    SetClassifier(kSvm);
}

void ofApp::trainingButtonPressed() {
    
    //Open the Open File Dialog
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a csv for training");
    
    //Check if the user opened a file
    if (openFileResult.bSuccess){
        LoadData(openFileResult.getPath());
        
        if (classifier_) {
            delete classifier_;
        }
        
        if (classifier_type_ == kKnn) {
            classifier_ = new KnnClassifier(3);
        } else if (classifier_type_ == kBayes) {
            classifier_ = new BayesClassifier();
        } else if (classifier_type_ == kSvm) {
            classifier_ = new SvmClassifier();
        }
        
        classifier_->Train(data_, label_);
    }
    
}

void ofApp::classifyButtonPressed() {
    //Open the Open File Dialog
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a csv for training");
    
    //Check if the user opened a file
    if (openFileResult.bSuccess){
        LoadData(openFileResult.getPath());
        
        ClassifyData();
    }
}
