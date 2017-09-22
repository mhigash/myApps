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

class MnistTest {
	typedef std::vector<std::pair<unsigned char*, unsigned char>> ImageLabelList;

	ImageLabelList train_images_;
	ImageLabelList t10k_images_;

	NeuralNetwork the_brain_;

	bool Load(const std::string &path, const std::string &kind, ImageLabelList *images);

public:
	MnistTest();
	~MnistTest();

	bool LoadData(const std::string &path);
	bool Train();
};


#endif /* mnist_test_hpp */
