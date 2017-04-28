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
	float eta_;
	int n_iter_;

	float w0_;
	std::vector<float> w_;
	std::vector<float> errors_;

	float NetInput(const std::vector<float> &x);
    
public:
    PerceptronClassifier(float eta = 0.01f, int n_iter = 10);
    ~PerceptronClassifier();
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};

#endif /* perceptron_classifier_hpp */
