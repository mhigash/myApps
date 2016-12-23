//
//  util.cpp
//  image_classification
//
//  Created by masashi.higashimura on 2016/12/11.
//
//

#include "util.hpp"

bool loadPoints3(const string& filepath, vector<cv::Vec3f>& pointList)
{
    ifstream file(filepath);
    if (!file.is_open())
        return false;
    
    cv::Vec3f v3;
    
    while (!file.eof()) {
        string val[4];
        
        file >> val[0];
        file >> val[1];
        file >> val[2];
        
        v3.val[0] = static_cast<float>(atof(val[0].c_str()));
        v3.val[1] = static_cast<float>(atof(val[1].c_str()));
        v3.val[2] = static_cast<float>(atof(val[2].c_str()));
        
        pointList.push_back(v3);
    }
    
    return true;
}

vector<string> Split(const string &s, char delim) {
    vector<string> elems;
    string item;
    
    for (char ch: s) {
        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}

bool LoadCsvAsImage(const string& filepath, char delimiter, cv::Mat& image)
{
    ifstream file(filepath);
    if (!file.is_open())
        return false;
    
    vector<string> elements;
    
    int rows = 0;
//    char delimiter = '\t';
    
    while (!file.eof()) {
        string line;
        getline(file, line);
        
        if (line.length() < 2)
            continue;
        
        elements = Split(line, delimiter);
        
        float* array = new float[elements.size()];
        for (int i = 0; i < elements.size(); i++) {
            array[i] = atof(elements[i].c_str());
        }
        
        cv::Mat row = cv::Mat(1, static_cast<int>(elements.size()), CV_32F, array);
        
        if (rows == 0) {
            image = cv::Mat(1, static_cast<int>(elements.size()), CV_32F, array);
        } else {
            image.push_back(row);
        }
        
        rows++;
    }
    
    return true;
}

//template <typename T>
//vector<size_t> ArgSort(const vector<T> &v) {
//    
//    // initialize original index locations
//    vector<size_t> idx(v.size());
//    
//    iota(idx.begin(), idx.end(), 0);
//    
//    // sort indexes based on comparing values in v
//    sort(idx.begin(), idx.end(),
//         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
//    
//    return idx;
//}

