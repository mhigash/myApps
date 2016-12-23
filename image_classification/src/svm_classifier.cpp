//
//  svm_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/15.
//
//

#include "svm.h"
#include "svm_classifier.hpp"

using namespace std;

SvmClassifier::SvmClassifier() {

}

SvmClassifier::~SvmClassifier() {
    delete[] prob_.y;
    delete[] prob_.x;
    delete[] x_space_;
}


//
// Train on data (2d matrix whose cols means dimention and row means n
//
bool SvmClassifier::Train(const cv::Mat& data, const cv::Mat& labels) {
    // data             labels
    // x1, y1, ....,    l1
    // x2, y2, ....,    l2
    // ....,
    // xn, yn, ....,    ln
    
    // README in svm helped me so much
    
    prob_.l = data.rows;
    prob_.y = new double[data.rows];
    prob_.x = new svm_node*[data.rows];
    x_space_ = new svm_node[data.rows * (data.cols + 1)];
    
    int index = 0;
    
    for (int r = 0; r < data.rows; r++) {
        float label = labels.at<float>(r, 0);
        
        prob_.y[r] = label;
        prob_.x[r] = &x_space_[index];
        
        for (int c = 0; c < data.cols; c++) {
            x_space_[index].index = c + 1;
            x_space_[index].value = data.at<float>(r, c);
            index++;
        }
        x_space_[index++].index = -1;
    }
    
    
    memset(&param_, 0x00, sizeof(param_));
    
    // default values
    param_.svm_type = C_SVC;
    param_.kernel_type = RBF;
    param_.degree = 3;
    param_.gamma = 1.0/static_cast<double>(data.cols);	// 1/num_features
    param_.coef0 = 0;
    param_.nu = 0.5;
    param_.cache_size = 100;
    param_.C = 1;
    param_.eps = 1e-3;
    param_.p = 0.1;
    param_.shrinking = 1;
    param_.probability = 0;
    param_.nr_weight = 0;
    param_.weight_label = NULL;
    param_.weight = NULL;
    
    // train
    model_ = svm_train(&prob_, &param_);

    return true;
}

//
// Classify points by computing probabilities
// for each class and return most probable label
//
int SvmClassifier::Classify(const cv::Mat& data) {
    
    if (data.rows != 1) {
        return 0;
    }
    
    svm_node* x = new svm_node[data.cols + 1];
    
    for (int c = 0; c < data.cols; c++) {
        x[c].index = c + 1;
        x[c].value = data.at<float>(0, c);
    }
    
    x[data.cols].index = -1;
    
    double d = svm_predict(model_, x);
    
    delete[] x;
    
    return static_cast<int>(d);
}

