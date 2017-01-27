//
//  knn_classifier.hpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#ifndef knn_hpp
#define knn_hpp

#include "classifier.h"

class KnnClassifier : public Classifier {
    cv::Mat samples_;
    cv::Mat labels_;
    int k_;
    
    float EuclidDiatance(const cv::Mat point1, const cv::Mat& point2);
    
public:
    KnnClassifier(int k);
    ~KnnClassifier();
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};

#endif /* knn_hpp */
