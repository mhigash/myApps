//
//  bayes_classifier.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/15.
//
//

#include "bayes_classifier.hpp"

//
// Train on data (2d matrix whose cols means dimention and row means n
//
bool BayesClassifier::Train(const cv::Mat& data, const cv::Mat& labels) {
    // data             labels
    // x1, y1, ....,    l1
    // x2, y2, ....,    l2
    // ....,
    // xn, yn, ....,    ln
    
    int index = 0;
    
    // Finding unique labels and determine index
    for (int r = 0; r < data.rows; r++) {
        float label = labels.at<float>(r, 0);
        
        if (indices_of_label_.find(label) == indices_of_label_.end()) {
            indices_of_label_[label] = index++;
            labels_.push_back(label);
        }
    }
    
    means_ = cv::Mat::zeros(static_cast<int>(indices_of_label_.size()), data.cols, CV_32F);
    vars_ = cv::Mat::zeros(static_cast<int>(indices_of_label_.size()), data.cols, CV_32F);
    
    std::map<float, int> count;
    
    // count up and sum up for mean
    for (int r = 0; r < data.rows; r++) {
        float label = labels.at<float>(r, 0);
        
        if (count.find(label) == count.end()) {
            count[label] = 1;
        } else {
            count[label]++;
        }
        
        int row_for_stats = indices_of_label_[label];
        
        for (int c = 0; c < data.cols; c++) {
            means_.at<float>(row_for_stats, c) += data.at<float>(r, c);
        }
    }
    
    // divide for mean
    for (int r = 0; r < means_.rows; r++) {
        for (int c = 0; c < means_.cols; c++) {
            means_.at<float>(r, c) /= count[static_cast<float>(r + 1)];
        }
    }
    
    // sum up for variance
    for (int r = 0; r < data.rows; r++) {
        float label = labels.at<float>(r, 0);
        
        for (int c = 0; c < data.cols; c++) {
            int row_for_stats = indices_of_label_[label];
            
            float diff = data.at<float>(r, c) - means_.at<float>(row_for_stats, c);
            vars_.at<float>(row_for_stats, c) += diff * diff;
        }
    }
    
    // divide for variance
    for (int r = 0; r < vars_.rows; r++) {
        for (int c = 0; c < vars_.cols; c++) {
            vars_.at<float>(r, c) /= count[static_cast<float>(r + 1)];
        }
    }
  
    // dump for check.
    std::cout << "indices_of_label_ =[";
    for (std::map<float, int>::iterator itr = indices_of_label_.begin(); itr != indices_of_label_.end(); itr++) {
        std::cout << "  " << itr->first << "," << itr->second << std::endl;
    }
    std::cout << "]" << std::endl;
    
    std::cout << "labels_ =[";
    for (std::vector<float>::iterator itr = labels_.begin(); itr != labels_.end(); itr++) {
        std::cout << "  " << *itr << std::endl;
    }
    std::cout << "]" << std::endl;
    
    std::cout << "count =[";
    for (std::map<float, int>::iterator itr = count.begin(); itr != count.end(); itr++) {
        std::cout << "  " << itr->first << "," << itr->second << std::endl;
    }
    std::cout << "]" << std::endl;
    
    std::cout << "means =" << means_ << std::endl;
    std::cout << "vars =" << vars_ << std::endl;
    
    return true;
}

//
// Classify points by computing probabilities
// for each class and return most probable label
//
int BayesClassifier::Classify(const cv::Mat& data) {

    if (data.cols != means_.cols)
        return 0;
    
    if (data.rows != 1) {
        return 0;
    }
    
    //
    // compute probabilities for each class
    //
    std::vector<float> probabilities;
    
    for (int m = 0; m < means_.rows; m++) {
        cv::Mat mean = means_.row(m).clone();
        cv::Mat var = vars_.row(m).clone();
        
        probabilities.push_back(Gauss(mean, var, data.clone()));
    }
    
    //
    // get index of highest probability, this gives class label
    // I used slow linear search because "distance" didn't work well.
    //
    long arg_max = 0;
    long index = 0;
    float max_prob = 0.0f;
    for (std::vector<float>::iterator itr = probabilities.begin(); itr != probabilities.end(); itr++) {
        if (max_prob < *itr) {
            max_prob = *itr;
            arg_max = index++;
        }
    }
//    arg_max = std::distance(probabilities.begin(), max_element(probabilities.begin(), probabilities.end()));

    // "indices_of_label_" is a map whose key is label and value is index
    int estimated_label = labels_[arg_max];
    
//    std::cout << "arg_max = " << arg_max << std::endl;
//    std::cout << "est_label = " << estimated_label << std::endl;
    
    return estimated_label;
}

//
// Evaluate gaussian in d-dimension with indipendent
// mean m and variance v at the points in the rows of x
//
float BayesClassifier::Gauss(const cv::Mat mean, const cv::Mat& var, const cv::Mat& point) {
    
    float d = point.cols;
    
    // covariance matrix
    cv::Mat S = cv::Mat::zeros(var.cols, var.cols, CV_32F);
    cv::Mat x = point.clone();
    
    for (int c = 0; c < var.cols; c++) {
        S.at<float>(c, c) = 1.0f / var.at<float>(0, c);
    }
    
    // subtract mean
    for (int i = 0; i < x.cols; i++) {
        x.at<float>(0, i) -= mean.at<float>(0, i);
    }
    
    // product of probabilities
    cv::Mat temp = x * S * x.t();
    float prod = temp.at<float>(0, 0);
    float y = exp(-0.5 * prod);
    
//    cv::Mat temp = S * x.t() * x;
//    cv::Mat prod = cv::Mat::zeros(temp.cols, temp.cols, temp.type());
//    for (int c = 0; c < var.cols; c++) {
//        prod.at<float>(c, c) = temp.at<float>(c, c);
//    }
//    
//    cv::Mat y;
//    cv::exp(-0.5 * prod, y);
    
    // product of variance
    float prod_v = 1.0f;
    for (int i = 0; i < var.cols; i++) {
        prod_v *= var.at<float>(0, i);
    }

    const float pi = 3.14159265358979f;
    
    float gauss = y * pow(2 * pi, -d / 2.0f) / (sqrt(prod_v) + 1e-6);
//    std::cout << "S =" << S << std::endl;
//    std::cout << "x =" << x << std::endl;
    return gauss;
}
