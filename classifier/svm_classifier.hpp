//
//  svm.hpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/15.
//
//

#ifndef svm_classifier
#define svm_classifier

#include <stdio.h>

#include "classifier.h"
#include "svm.h"

class SvmClassifier : public Classifier {
    
    struct svm_parameter param_;		// set by parse_command_line
    struct svm_problem prob_;		// set by read_problem
    struct svm_model *model_;
    struct svm_node *x_space_;

    
public:
    SvmClassifier();
    ~SvmClassifier();
    
    bool Train(const cv::Mat& data, const cv::Mat& label);
    int Classify(const cv::Mat& data);
};


#endif /* svm_classifier */
