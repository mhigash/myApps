#include "MeasurementDataSet.h"


MeasurementDataSet::MeasurementDataSet(void)
{
	measurement_data_id_ = 0;
	memset(&image8u3_, 0, sizeof(image8u3_));
	memset(&image32f_, 0, sizeof(image32f_));
	memset(&measurement_data_, 0, sizeof(measurement_data_));
	memset(&image_setting_, 0, sizeof(image_setting_));
	memset(&rgb_color_setting_, 0, sizeof(rgb_color_setting_));
	memset(&pseudo_color_setting_, 0, sizeof(pseudo_color_setting_));

	image_to_data_[HS_IMAGE_DATA_TYPE_TRISTIMULUS_X] = HS_DATA_TYPE_TRISTIMULUS_X;
	image_to_data_[HS_IMAGE_DATA_TYPE_TRISTIMULUS_Y] = HS_DATA_TYPE_TRISTIMULUS_Y;
	image_to_data_[HS_IMAGE_DATA_TYPE_TRISTIMULUS_Z] = HS_DATA_TYPE_TRISTIMULUS_Z;
	image_to_data_[HS_IMAGE_DATA_TYPE_CHROMATICITY_X] = HS_DATA_TYPE_CHROMATICITY_X;
	image_to_data_[HS_IMAGE_DATA_TYPE_CHROMATICITY_Y] = HS_DATA_TYPE_CHROMATICITY_Y;
	image_to_data_[HS_IMAGE_DATA_TYPE_CHROMATICITY_U] = HS_DATA_TYPE_CHROMATICITY_U;
	image_to_data_[HS_IMAGE_DATA_TYPE_CHROMATICITY_V] = HS_DATA_TYPE_CHROMATICITY_V;
	image_to_data_[HS_IMAGE_DATA_TYPE_LAB_L] = HS_DATA_TYPE_LAB_L;
	image_to_data_[HS_IMAGE_DATA_TYPE_LAB_A] = HS_DATA_TYPE_LAB_A;
	image_to_data_[HS_IMAGE_DATA_TYPE_LAB_B] = HS_DATA_TYPE_LAB_B;
}

MeasurementDataSet::~MeasurementDataSet(void)
{
	Clear();
}

void MeasurementDataSet::PrintError(HsError error)
{
	char error_string[256];
	memset(error_string, 0, sizeof(error_string));

	HsError ret = hsGetErrorString(error, sizeof(error_string), error_string);
	std::cout << error_string << std::endl;
}

void MeasurementDataSet::Clear()
{
	if (image32f_.pixels != nullptr) {
		hsDestroyImage32f(&image32f_);
	}

	if (image8u3_.pixels != nullptr) {
		hsDestroyImage8u3(&image8u3_);
	}
}

HsError MeasurementDataSet::Initialize()
{
	HsConfiguration config;
	HsError ret = hsInitialize("D:\\HS\\source\\HS-5000\\Objects\\Calibration\\SR-5000\\", &config);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	return ret;
}

HsError MeasurementDataSet::Load(const std::string& filename)
{
	HsError ret = hsLoadMeasurementData(filename.c_str(), nullptr, &measurement_data_id_);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	ret = hsGetMeasurementData(measurement_data_id_, &measurement_data_);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	ret = hsCreateImage8u3(measurement_data_.image_width, measurement_data_.image_height, &image8u3_);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	ret = hsCreateImage32f(measurement_data_.image_width, measurement_data_.image_height, &image32f_);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	ret = hsGetMeasurementDataImageSetting(measurement_data_id_, &image_setting_);
	if (ret != HS_ERROR_NONE) {
		PrintError(ret);
		return ret;
	}

	return ret;
}

HsError MeasurementDataSet::GetImage(HsImageDataType image_type, int wavelength, ofImage& image)
{
	HsError ret = HS_ERROR_NONE;

	if (image_type == HS_IMAGE_DATA_TYPE_RGB) {
		ret = hsGetRGBColorImage(measurement_data_id_, rgb_color_setting_, &image8u3_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}
	} else if (image_type == HS_IMAGE_DATA_TYPE_SPECTRAL_RADIANCE) {
		ret = hsGetSpectralImage(measurement_data_id_, wavelength, &image32f_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}

		ret = hsToSpectralColor(&image32f_, wavelength, nullptr, &image8u3_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}
	} else {
		HsDataType data_type = image_to_data_[image_type];

		ret = hsGetMeasurementImage(measurement_data_id_, data_type, &image32f_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}

		pseudo_color_setting_.color_setting = image_setting_.color_setting[data_type];

		ret = hsToPseudoColor(pseudo_color_setting_, &image32f_, nullptr, &image8u3_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}
	}

	ToOfImage(image8u3_, image);
	return ret;
}

void MeasurementDataSet::ToOfImage(const HsImage8u3 &src_image, ofImage& image)
{
	// Swap pixel order
	for (int y = 0; y < src_image.height; y++) {
		for (int x = 0; x < src_image.width; x++) {
			int index0 = y * src_image.width * HS_BYTES_PER_PIXEL_8U3 + x * HS_BYTES_PER_PIXEL_8U3;
			int index2 = index0 + 2;

			unsigned char pixel0 = src_image.pixels[index0];
			unsigned char pixel2 = src_image.pixels[index2];

			src_image.pixels[index0] = pixel2;
			src_image.pixels[index2] = pixel0;
		}
	}

	image.setFromPixels(
		src_image.pixels,
		src_image.width,
		src_image.height,
		ofImageType::OF_IMAGE_COLOR,
		true);
	
}

HsError MeasurementDataSet::GetHistogram(HsImageDataType image_type, float bin, std::vector<int>& histogram)
{
	HsError ret = HS_ERROR_NONE;

	if (image_type == HS_IMAGE_DATA_TYPE_RGB) {
		return ret;
	} else if (image_type == HS_IMAGE_DATA_TYPE_SPECTRAL_RADIANCE) {
		int wavelength = 555;

		ret = hsGetSpectralImage(measurement_data_id_, wavelength, &image32f_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}
	} else {
		HsDataType data_type = image_to_data_[image_type];

		ret = hsGetMeasurementImage(measurement_data_id_, data_type, &image32f_);
		if (ret != HS_ERROR_NONE) {
			PrintError(ret);
			return ret;
		}
	}

	HsHistogramData histo;
	ret = hsCreateHistogram(&image32f_, nullptr, bin, &histo);

	histogram.clear();
	for (int i = 0; i < histo.bins; i++) {
		histogram.push_back(histo.counts[i]);
	}

	ret = hsDestroyHistogram(&histo);

	HsPoint point;
	point.x = measurement_data_.image_width / 2;
	point.y = measurement_data_.image_height / 2;

	HsPixelData pixelData;

	ret = hsGetPixelData(measurement_data_id_, point, &pixelData);

	//pixelData.

	return ret;
}

void MeasurementDataSet::GetData(HsMeasurementData *measurement_data)
{
	*measurement_data = measurement_data_;
}

void MeasurementDataSet::GetColorSetting(HsImageDataType image_type, HsColorSetting *color_setting)
{
	HsDataType data_type = image_to_data_[image_type];
	*color_setting = image_setting_.color_setting[data_type];
}

void MeasurementDataSet::SetColorSetting(HsImageDataType image_type, const HsColorSetting &color_setting)
{
	HsDataType data_type = image_to_data_[image_type];
	image_setting_.color_setting[data_type] = color_setting;
}

void MeasurementDataSet::GetStatistics(HsImageDataType image_type, HsStatistics *statistics)
{
	HsDataType data_type = image_to_data_[image_type];
	*statistics = measurement_data_.statistics[data_type];
}

