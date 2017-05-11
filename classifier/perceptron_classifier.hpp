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

// Perceptron classifier.
class PerceptronClassifier : public Classifier {
	// Learning rate (between 0.0 and 1.0)
	float eta_;
	// Passes over the training dataset.
	int n_iter_;

	float w0_;
	// Weights after fitting.
	std::vector<float> w_;
	// Number of misclassifications (updates) in each epoch.
	std::vector<int> errors_;

    float NetInput(const std::vector<float> &x);
    float Predict(const cv::Mat &data);
    
public:
    PerceptronClassifier(float eta = 0.01f, int n_iter = 30);
    ~PerceptronClassifier();
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};

#endif /* perceptron_classifier_hpp */
