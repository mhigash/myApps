//
//  neural_network.cpp
//  ocr
//
//  Created by masashi.higashimura on 2017/09/01.
//
//

#include "mnist_test.hpp"

#include <thread>

int big_endian(int little) {
    int big = 0;
    big |= (little & 0xFF000000) >> 24;
    big |= (little & 0x00FF0000) >> 8;
    big |= (little & 0x0000FF00) << 8;
    big |= (little & 0x000000FF) << 24;
    return big;
}

MnistTest::MnistTest()
: image_rows_(0)
, image_cols_(0)
{
}

MnistTest::~MnistTest() {
    // need to wait until the thread will be stopped.
    cancel_requested_ = true;
    thread_->join();

    for (auto im_lb : train_images_) {
        delete[] im_lb.first;
    }
    train_images_.clear();
    
    for (auto im_lb : t10k_images_) {
        delete[] im_lb.first;
    }
    t10k_images_.clear();
}

bool MnistTest::Load(const std::string &path,
					 const std::string &kind,
					 ImageLabelList *images) {
    std::string label_path = path + kind + "-labels.idx1-ubyte";
    std::string images_path = path + kind + "-images.idx3-ubyte";
    
    FILE* lbpath = fopen(label_path.c_str(), "rb");
    if (lbpath == nullptr)
        return false;
    
    int magic, n;
    fread(&magic, sizeof(int), 1, lbpath);
    fread(&n,     sizeof(int), 1, lbpath);

    magic = big_endian(magic);
    n     = big_endian(n);
    
    unsigned char *labels = new unsigned char[n];
    fread(labels, sizeof(unsigned char), n, lbpath);
    fclose(lbpath);

    FILE* imgpath = fopen(images_path.c_str(), "rb");
    if (imgpath == nullptr)
        return false;

    int rows, cols;
    fread(&magic, sizeof(int), 1, imgpath);
    fread(&n,     sizeof(int), 1, imgpath);
    fread(&rows,  sizeof(int), 1, imgpath);
    fread(&cols,  sizeof(int), 1, imgpath);
    
    magic = big_endian(magic);
    n     = big_endian(n);
    rows  = big_endian(rows);
    cols  = big_endian(cols);
    
    image_rows_ = rows;
    image_cols_ = cols;
    
    int size = rows * cols;
    
    unsigned char* buf = new unsigned char[size];
    for (int i = 0; i < n; i++) {
        fread(buf, sizeof(unsigned char), size, imgpath);
        
        unsigned char* image = new unsigned char[size];;
		memcpy(image, buf, size);
        //image.allocate(cols, rows, ofImageType::OF_IMAGE_GRAYSCALE);
        //image.setFromPixels(buf, cols, rows, ofImageType::OF_IMAGE_GRAYSCALE);
        
        images->push_back(std::make_pair(image, labels[i]));
    }
    
    fclose(imgpath);
    
    delete[] labels;
    delete[] buf;
    return true;
}

bool MnistTest::StartTraining() {
    cancel_requested_ = false;
    thread_.reset(new std::thread(&MnistTest::Train, this));
    return true;
}

bool MnistTest::Train() {

//    ImageLabelList::iterator iter;

    // Train the brain
//	the_brain_.Initialize(4, 3, 3);
	the_brain_.Initialize(kInputNum, 50, kOutputNum);
    the_brain_.SetLearningRate(0.2);
    the_brain_.SetMomentum(true, 0.9);
    
    progress_.error = 1.0;
    progress_.training_count = 0;
    progress_.max_image_count = kMaxTrainingImageCount;
    progress_.max_training_count = kMaxTrainingCount;
    
    std::string pre_training_path = "/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PreTraining.txt";
    std::string post_training_path = "/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/PostTraining.txt";
    std::string result_path = "/Users/hgsmrmss/Documents/code_samples/openframeworks/of_v0.9.8_osx_release/apps/myApps/ocr/bin/result.txt";
    
	the_brain_.DumpData(pre_training_path.c_str());

	time_t start, finish;
	double elapsed_time;

	time(&start);// get the start time

	//while (error > 0.05 && c < 50000) {
	while (progress_.error > 0.05 && progress_.training_count < kMaxTrainingCount) {
        if (cancel_requested_)
            return false;
        
        progress_.error = 0;
		progress_.image_count = 0;
        progress_.training_count++;
        
        //for (iter = train_images_.begin(); iter != train_images_.end(); iter++) {
        for (auto im_lb : train_images_) {
			progress_.image_count++;

			unsigned char *data = im_lb.first;
			unsigned char label = im_lb.second;

			double one_hot[kOutputNum];
			memset(one_hot, 0, sizeof(one_hot));
			one_hot[label] = 1.0;

			for (int i = 0; i < kInputNum; i++) {
				the_brain_.SetInput(i, data[i]);
			}

			for (int i = 0; i < kOutputNum; i++) {
				the_brain_.SetDesiredOutput(i, one_hot[i]);
			}

			the_brain_.FeedForward();
			progress_.error += the_brain_.CalculateError();
			the_brain_.BackPropagate();

			if (progress_.image_count >= kMaxTrainingImageCount) break; // DEBUG: 60000 images and 50 counts cannot end in 12 hours!
		}

		progress_.error /= progress_.image_count;
    }
	the_brain_.DumpData(post_training_path.c_str());

	std::ofstream result(result_path);

	time(&finish);// get the end time
	elapsed_time = difftime(finish, start);

	result << "It took " << elapsed_time << " seconds." << std::endl;
	result << "max training count: " << kMaxTrainingImageCount << std::endl;
	result << "max test count:     " << kMaxTestImageCount << std::endl;
	result << "iteration count:    " << progress_.training_count << std::endl;

	int correct_count = 0;
	progress_.image_count = 0;

	//for (iter = t10k_images_.begin(); iter != t10k_images_.end(); iter++) {
	//for (iter = train_images_.begin(); iter != train_images_.end(); iter++) {
    for (auto im_lb : train_images_) {
        if (cancel_requested_)
            return false;
        
		progress_.image_count++;
		unsigned char *data = im_lb.first;
		unsigned char label = im_lb.second;

		for (int i = 0; i < kInputNum; i++) {
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

		if (progress_.image_count >= kMaxTestImageCount) break; // DEBUG:
	}

	float ratio = static_cast<float>(correct_count) /
	   	static_cast<float>(progress_.image_count);
	result << "correct ratio: " << ratio << std::endl;

	return true;
}

bool MnistTest::LoadData(const std::string &path) {
	bool is_loaded = false;
	is_loaded = Load(path, kTrain, &train_images_);
	is_loaded = Load(path, kT10k,  &t10k_images_);
	return true;
}

int MnistTest::GetImageCount(const std::string &kind) {
    if (kind == kTrain) {
        return train_images_.size();
    } else if (kind == kT10k) {
        return t10k_images_.size();
    }
    
    return -1;
}

bool MnistTest::GetImage(std::string &kind,
                         int index,
                         ImageAndLabel &image_and_label) {
    if (kind == kTrain) {
        image_and_label = train_images_[index];
    } else if (kind == kT10k) {
        image_and_label = t10k_images_[index];
    } else {
        return false;
    }
        
    return true;
}
