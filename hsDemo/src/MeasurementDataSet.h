#pragma once

#include "ofMain.h"

#include "hs_api.h"

class MeasurementDataSet
{
	HsImage8u3 image8u3_;
	HsImage32f image32f_;
	HsMeasurementData measurement_data_;
	HsMeasurementDataImageSetting image_setting_;
	HsRGBColorSetting rgb_color_setting_;
	HsPseudoColorSetting pseudo_color_setting_;

	std::map<HsImageDataType, HsDataType> image_to_data_;

	int measurement_data_id_;

	void Clear();
	void PrintError(HsError error);
public:

public:
	MeasurementDataSet(void);
	~MeasurementDataSet(void);

	HsError Initialize();
	HsError Load(const std::string& filename);
	HsError GetImage(HsImageDataType image_type, int wavelength, ofImage& image);
	HsError GetHistogram(HsImageDataType image_type, float bin, std::vector<int>& histogram);
	//HsError getPixelData(int x, int y, 
};

