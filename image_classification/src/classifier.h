//
//  classifier.h
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/15.
//
//

#ifndef classifier_h
#define classifier_h

#include <stdio.h>
#include <limits>
#include <opencv2/opencv.hpp>

class Classifier {
protected:
    
public:
    Classifier() {}
    virtual ~Classifier() {}
    
    virtual bool Train(const cv::Mat& data, const cv::Mat& labels) = 0;
    virtual int Classify(const cv::Mat& data) = 0;
};

#endif /* classifier_h */
