//
//  util.hpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>

#include <opencv2/opencv.hpp>

bool loadPoints3(const std::string& filepath, std::vector<cv::Vec3f>& pointList);
bool LoadCsvAsImage(const std::string& filepath, char delimiter, cv::Mat& image);


#endif /* util_hpp */
