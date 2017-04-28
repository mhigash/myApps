//
//  perceptron_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#include "perceptron_classifier.hpp"
#include "util.hpp"


PerceptronClassifier::PerceptronClassifier(float eta, int n_iter) {
	eta_ = eta;
	n_iter_ = n_iter;
}

PerceptronClassifier::~PerceptronClassifier() {
    
}

bool PerceptronClassifier::Train(const cv::Mat& data, const cv::Mat& labels) {

	//w_ = cv::Mat::zeros(data.rows + 1, 1, CV_32F);
	w_.clear();
	w_.reserve(data.rows);

	w0_ = 0.0f;

	for (int n = 0; n < n_iter_; n++) {

		for (int r = 0; r < data.rows; r++) {
			cv::Mat xi = data.row(r);

			float target = labels.at<float>(r, 0);
			float update = eta_ * (target - Classify(xi));
		}

	}
    return true;
}

int PerceptronClassifier::Classify(const cv::Mat& data)
{
	if (data.rows != 1) {
		return 0;
	}

	std::vector<float> x;

	for (int c = 0; c < data.cols; c++) {
		x.push_back(data.at<float>(0, c));
	}

	// Return class label after unit step
	float net_input = NetInput(x);

	return net_input >= 0.0f ? 1.0f : -1.0f;
}

float PerceptronClassifier::NetInput(const std::vector<float> &x)
{
	// Calculate net input

	float dot = 0;
	for (int i = 0; i < x.size(); i++) {
		dot += x[i] * w_[i];
	}
	dot += w0_;

	return dot;
}
