//
//  knn_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#include "knn_classifier.hpp"
#include "util.hpp"

typedef struct _DistanceWithIndex
{
	float distance;
	int index;
} DistanceWithIndex;

bool operator<(const DistanceWithIndex& left, const DistanceWithIndex& right)
{
	return left.distance < right.distance;
}

KnnClassifier::KnnClassifier(int k) {
    k_ = k;
}

KnnClassifier::~KnnClassifier() {
    
}

bool KnnClassifier::Train(const cv::Mat& data, const cv::Mat& labels) {
    
    samples_ = data.clone();
    labels_ = labels.clone();
    
    return true;
}

int KnnClassifier::Classify(const cv::Mat& data) {
    
    if (samples_.cols != data.cols) {
        std::cout << "Cols mismatch." << samples_.cols << "," << data.cols << std::endl;
        return 0;
    }
    
    if (data.rows != 1) {
        std::cout << "Rows is not 1." << std::endl;
        return 0;
    }

	std::vector<DistanceWithIndex> distances;

	for (int r = 0; r < samples_.rows; r++) {
		DistanceWithIndex distance = {
			EuclidDiatance(samples_.row(r), data),
			r
		};

		distances.push_back(distance);
	}

	std::sort(distances.begin(), distances.end());
    
    std::map<float, int> votes;
    
    for (int i = 0; i < k_; i++) {
        float label = labels_.at<float>(distances[i].index, 0);
        
        if (votes.find(label) == votes.end()) {
            votes[label] = 1;
        } else {
            votes[label]++;
        }
    }
    
    std::map<float, int>::iterator itr = std::max_element(votes.begin(), votes.end());
    
    return itr->first;
}

float KnnClassifier::EuclidDiatance(const cv::Mat point1, const cv::Mat& point2) {
    
    float sum = 0.0f;
    for (int c = 0; c < point1.cols; c++) {
        float value1 = point1.at<float>(0, c);
        float value2 = point2.at<float>(0, c);
        sum += (value1 - value2) * (value1 - value2);
    }
    
    return sqrt(sum);
}
