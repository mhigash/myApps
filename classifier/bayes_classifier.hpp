//
//  bayes_classifier.hpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/15.
//
//

#ifndef bayes_hpp
#define bayes_hpp

#include <stdio.h>

#include "classifier.h"

class BayesClassifier : public Classifier {
    cv::Mat means_;
    cv::Mat vars_;
    
    std::map<float, int> indices_of_label_;
    std::vector<float> labels_;
    
    
    float Gauss(const cv::Mat mean, const cv::Mat& var, const cv::Mat& point);
    
public:
    BayesClassifier() {};
    ~BayesClassifier() {};
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};


#endif /* bayes_hpp */
