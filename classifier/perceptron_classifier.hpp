//
//  perceptron_classifier.hpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#ifndef perceptron_classifier_hpp
#define perceptron_classifier_hpp

#include "classifier.h"

class PerceptronClassifier : public Classifier {
    cv::Mat samples_;
    cv::Mat labels_;
    int k_;
    
    float EuclidDiatance(const cv::Mat point1, const cv::Mat& point2);
    
public:
    PerceptronClassifier(int k);
    ~PerceptronClassifier();
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};

#endif /* perceptron_classifier_hpp */
