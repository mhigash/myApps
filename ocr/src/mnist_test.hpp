//
//  mnist_test.hpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#ifndef mnist_test_hpp
#define mnist_test_hpp

#include <time.h>

#include <fstream>
#include <limits>
#include <string>
#include <vector>

#include <thread>
//#include <shared_ptr>

//#include "neural_network.hpp"
#include "MyNeuralNetwork.h"

static const std::string kTrain = "train";
static const std::string kT10k = "t10k";

static const int kInputNum = 784; // 28 rows * 28 cols in image
static const int kOutputNum = 10;
static const int kMaxTrainingCount = 500;
static const int kMaxTrainingImageCount = 4096;
static const int kMaxTestImageCount = 128;


typedef std::pair<unsigned char*, unsigned char> ImageAndLabel;
typedef std::vector<std::pair<unsigned char*, unsigned char>> ImageLabelList;

struct Progress {
    int image_count;
    int training_count;
    int max_image_count;
    int max_training_count;
    double error;
};

class MnistTest {
	ImageLabelList train_images_;
	ImageLabelList t10k_images_;
    int image_rows_;
    int image_cols_;
    
	NeuralNetwork the_brain_;

    bool cancel_requested_;
    Progress progress_;
    
    std::shared_ptr<std::thread> thread_;
    
	bool Load(const std::string &path, const std::string &kind, ImageLabelList *images);
    bool Train();

public:
	MnistTest();
	~MnistTest();

	bool LoadData(const std::string &path);
    bool StartTraining();
    
    int GetImageCount(const std::string &kind);
    int GetImageWidth() { return image_cols_; }
    int GetImageHeight() { return image_rows_; }
    bool GetImage(std::string &kind,
                  int index,
                  ImageAndLabel &image_and_label);
    
    Progress progress() { return progress_; }
};


#endif /* mnist_test_hpp */
