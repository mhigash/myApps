//
//  iris_test.cpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#include "iris_test.hpp"

std::vector<std::string> Split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::string item;
    
#if 0
    for (char ch: s) {
#else
    for each (auto ch in s) {
#endif
        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        } else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}

IrisTest::IrisTest() {
}

IrisTest::~IrisTest() {
	FeatureLabelList::iterator iter;
	float *data = nullptr;

	for (iter = train_data_.begin(); iter != train_data_.end(); iter++) {
		data = iter->first;
		delete[] data;
	}
	train_data_.clear();

	for (iter = test_data_.begin(); iter != test_data_.end(); iter++) {
		data = iter->first;
		delete[] data;
	}
	test_data_.clear();
}

bool IrisTest::Train() {
	const int kInputNum = 2;
	const int kHiddenNum = 2;
	const int kOutputNum = 2;
	const int kMaxTrainingCount = 100;
	const int kMaxTestCount = 100;

	FeatureLabelList::iterator iter;
	int data_count = 0;

    // Train the brain
	the_brain_.Initialize(kInputNum, kHiddenNum, kOutputNum);
    the_brain_.SetLearningRate(0.2);
    the_brain_.SetMomentum(true, 0.9);
    
    int i;
    double error = 1.0;
    int c = 0;
    
	//the_brain_.DumpData("/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PreTraining.txt");
	the_brain_.DumpData("PreTraining.txt");

	time_t start, finish;
	double elapsed_time;

	// get the start time
	time(&start);

	while (error > 0.05 && c < 50000) {
        error = 0;
		data_count = 0;
        c++;
        
		for (iter = train_data_.begin(); iter != train_data_.end(); iter++) {
			data_count++;

			float *data = iter->first;
			unsigned char label = iter->second;

			double one_hot[kOutputNum];
			memset(one_hot, 0, sizeof(one_hot));
			one_hot[label] = 1.0;

			for (i = 0; i < kInputNum; i++) {
				the_brain_.SetInput(i, data[i]);
			}

			for (i = 0; i < kOutputNum; i++) {
				the_brain_.SetDesiredOutput(i, one_hot[i]);
			}

			the_brain_.FeedForward();
			error += the_brain_.CalculateError();
			the_brain_.BackPropagate();

			if (data_count >= kMaxTrainingCount) break;
		}

		error = error / static_cast<double>(data_count);
    }

	//the_brain_.DumpData("/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PostTraining.txt");
	the_brain_.DumpData("PostTraining.txt");

	std::ofstream result(".\\result.txt");

	// get the end time
	time(&finish);

	elapsed_time = difftime(finish, start);

	result << "It took " << elapsed_time << " seconds." << std::endl;
	result << "max training count: " << kMaxTrainingCount << std::endl;
	result << "max test count:     " << kMaxTestCount << std::endl;
	result << "iteration count:    " << c << std::endl;

	int correct_count = 0;
	data_count = 0;

	//for (iter = test_data_.begin(); iter != test_data_.end(); iter++) {
	for (iter = train_data_.begin(); iter != train_data_.end(); iter++) {
		data_count++;
		float *data = iter->first;
		unsigned char label = iter->second;

		for (i = 0; i < kInputNum; i++) {
			the_brain_.SetInput(i, data[i]);
		}

		the_brain_.FeedForward();

		int true_label = static_cast<int>(label);
		int classified_label = the_brain_.GetMaxOutputID();
		bool correct = (true_label == classified_label); 
		if (correct)
			correct_count++;

		result << "t,c = [" << true_label << ", " << 
			classified_label << "]; " << correct << std::endl;

		if (data_count >= kMaxTestCount) break; // DEBUG: 
	}

	float ratio = 
		static_cast<float>(correct_count) /
	   	static_cast<float>(data_count);
	result << "correct ratio: " << ratio << std::endl;

	return true;
}

bool IrisTest::LoadData(const std::string &path) {
	bool is_loaded = false;
	//is_loaded = Load(path, "train", &train_data_);
	//is_loaded = Load(path, "t10k",  &test_data_);
	
	std::ifstream file(path);
    if (!file.is_open())
        return false;
    
	std::vector<std::string> elements;
	std::set<std::string> labels;
    
    int rows = 0;
    char delimiter = ',';
    
    while (!file.eof()) {
		std::string line;
		std::getline(file, line);
        
        if (line.length() < 2)
            continue;
        
        elements = Split(line, delimiter);

		size_t features = elements.size() - 1;
        
        //float *array = new float[features];
        //for (int i = 0; i < features; i++) {
        //    array[i] = static_cast<float>(atof(elements[i].c_str()));
        //}
        float *array = new float[2];
        array[0] = static_cast<float>(atof(elements[0].c_str()));
        array[1] = static_cast<float>(atof(elements[2].c_str()));

		std::string label = elements[elements.size()-1];
		labels.insert(label);
		
		int d = std::distance(labels.begin(), labels.find(label));

		train_data_.push_back(std::make_pair(array, d));
        
        //delete[] array;
        rows++;
    }

	return true;
}
