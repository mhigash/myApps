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

//#include "neural_network.hpp"
#include "MyNeuralNetwork.h"

static const std::string kTrain = "train";
static const std::string kT10k = "t10k";

typedef std::pair<unsigned char*, unsigned char> ImageAndLabel;
typedef std::vector<std::pair<unsigned char*, unsigned char>> ImageLabelList;

class MnistTest {
	ImageLabelList train_images_;
	ImageLabelList t10k_images_;
    int image_rows_;
    int image_cols_;

	NeuralNetwork the_brain_;

	bool Load(const std::string &path, const std::string &kind, ImageLabelList *images);

public:
	MnistTest();
	~MnistTest();

	bool LoadData(const std::string &path);
	bool Train();
    
    int GetImageCount(const std::string &kind);
    int GetImageWidth() { return image_cols_; }
    int GetImageHeight() { return image_rows_; }
    bool GetImage(std::string &kind,
                  int index,
                  ImageAndLabel &image_and_label);
};


#endif /* mnist_test_hpp */
