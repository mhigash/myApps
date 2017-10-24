//
//  iris_test.hpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#ifndef iris_test_hpp
#define iris_test_hpp

#include <time.h>

#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <vector>

//#include "neural_network.hpp"
#include "MyNeuralNetwork.h"

class IrisTest {
	typedef std::vector<std::pair<float*, unsigned char>> FeatureLabelList;

	FeatureLabelList train_data_;
	FeatureLabelList test_data_;

	NeuralNetwork the_brain_;

public:
	IrisTest();
	~IrisTest();

	bool LoadData(const std::string &path);
	bool Train();
};


#endif /* iris_test_hpp */
