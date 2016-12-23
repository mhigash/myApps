//
//  knn_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#include "knn_classifier.hpp"
#include "util.hpp"

using namespace std;

// https://daisukekobayashi.com/blog/numpy-argsort-in-cpp/

template <typename Sequence, typename BinaryPredicate>
struct IndexCompareT {
    IndexCompareT(const Sequence& seq, const BinaryPredicate comp)
    : seq_(seq), comp_(comp) { }
    bool operator()(const size_t a, const size_t b) const
    {
        return comp_(seq_[a], seq_[b]);
    }
    const Sequence seq_;
    const BinaryPredicate comp_;
};

template <typename Sequence, typename BinaryPredicate>
IndexCompareT<Sequence, BinaryPredicate>
IndexCompare(const Sequence& seq, const BinaryPredicate comp)
{
    return IndexCompareT<Sequence, BinaryPredicate>(seq, comp);
}

template <typename Sequence, typename BinaryPredicate>
std::vector<size_t> ArgSort(const Sequence& seq, BinaryPredicate func)
{
    std::vector<size_t> index(seq.size());
    for (int i = 0; i < index.size(); i++)
        index[i] = i;
    
    std::sort(index.begin(), index.end(), IndexCompare(seq, func));
    
    return index;
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
        return 0;
    }
    
    if (data.rows != 1) {
        return 0;
    }
    
    vector<float> distances;
    
    for (int r = 0; r < samples_.rows; r++) {
        distances.push_back(EuclidDiatance(samples_.row(r), data));
    }
    
    // argsort
    vector<size_t> sorted_index = ArgSort(distances, std::less<float>());
    
    std::map<float, int> votes;
    
    for (int i = 0; i < k_; i++) {
        int index = static_cast<int>(sorted_index[i]);
        float label = labels_.at<float>(index, 0);
        
        if (votes.find(label) == votes.end()) {
            votes[label] = 1;
        } else {
            votes[label]++;
        }
    }
    
    map<float, int>::iterator itr = std::max_element(votes.begin(), votes.end());
    
    
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
