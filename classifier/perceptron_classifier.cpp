//
//  perceptron_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#include "perceptron_classifier.hpp"
#include "util.hpp"


PerceptronClassifier::PerceptronClassifier(int k) {
    k_ = k;
}

PerceptronClassifier::~PerceptronClassifier() {
    
}

bool PerceptronClassifier::Train(const cv::Mat& data, const cv::Mat& labels){
    return true;
}

int PerceptronClassifier::Classify(const cv::Mat& data)
{
    return 0;
}

