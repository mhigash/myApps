#include "image_document_list.h"


ImageDocumentList::ImageDocumentList(void)
{
}


ImageDocumentList::~ImageDocumentList(void)
{
	clear();
}

void ImageDocumentList::setup()
{
	std::vector<ImageDocument*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;
		imageDoc->setup();
	}
}

void ImageDocumentList::update()
{
	std::vector<ImageDocument*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;
		imageDoc->update();
	}
}

void ImageDocumentList::draw()
{
	std::vector<ImageDocument*>::iterator itr;

	ImageDocument *imageDoc1 = nullptr;
	ImageDocument *imageDoc2 = nullptr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;

		ofRectangle rect = imageDoc->getRect();

		if (imageDoc->getActiveType() == ACTIVE_1ST)
		{
			imageDoc1 = imageDoc;
		}
		else if(imageDoc->getActiveType() == ACTIVE_2ND)
		{
			imageDoc2 = imageDoc;
		}
		else
		{
		}

		imageDoc->draw();
	}

	// draw intersection
	if (imageDoc1 == nullptr || imageDoc2 == nullptr)
		return;

	ofPoint location = intersect.getCenter();
	location.z = 4;
#if 0
	ofSetColor(255, 255, 255, 128);
	ofDrawPlane(location, intersect.width, intersect.height);
#else
	intersectImage.bind();
	ofFill();
	// draw image
	ofSetColor(255);
	ofDrawPlane(location, intersectImage.getWidth(), -intersectImage.getHeight());
	intersectImage.unbind();
#endif

	// draw suporting rect
	ofSetColor(0, 255, 0);
	location.z = 5;
	ofNoFill();
				
	//ofDrawBox(location, 100, 100, 0);
}

void ImageDocumentList::drawInfo()
{
	std::vector<ImageDocument*>::iterator itr;

	int count = 1;
	int row = 1;
	char info[256];
	ofVec3f pos1, pos2;
	ofRectangle rect1, rect2;
	ImageDocument *imageDoc1 = nullptr;
	ImageDocument *imageDoc2 = nullptr;

	ofSetColor(0);

	for (itr = list.begin(); itr != list.end(); itr++, count++)
	{
		ImageDocument* imageDoc = *itr;
		ofVec3f pos = imageDoc->getPosition();
		ofRectangle rect = imageDoc->getRect();

		if (imageDoc->getActiveType() == ACTIVE_1ST)
		{
			ofSetColor(255, 0, 0);
			pos1 = pos;
			rect1 = rect;
			imageDoc1 = imageDoc;
		}
		else if(imageDoc->getActiveType() == ACTIVE_2ND)
		{
			ofSetColor(0, 0, 255);
			pos2 = pos;
			rect2 = rect;
			imageDoc2 = imageDoc;
		}
		else
		{
			ofSetColor(0);
		}

		// information1 location
		row++;
		sprintf(info, "%02d: x,y,z   = [%3.3f,%3.3f,%3.3f]", count, pos.x, pos.y, pos.z);
		ofDrawBitmapString(info, 15, 15 * row, 0);

		// information2 width and height
		row++;
		sprintf(info, "  : w,h     = [%3.3f,%3.3f]", rect.width, rect.height);
		ofDrawBitmapString(info, 15, 15 * row, 0);

		// information3 rect.
		row++;
		sprintf(info, "  : l,t,r,b = [%3.3f,%3.3f,%3.3f,%3.3f]",
			rect.getLeft(),
			rect.getTop(),
			rect.getRight(),
			rect.getBottom());
		ofDrawBitmapString(info, 15, 15 * row, 0);
	}

	ofSetColor(0);

	// diffrence between position 1 and 2
	row++;
	ofVec3f diff = pos2 - pos1;
	sprintf(info, "diff: x,y,z = [%3.3f,%3.3f,%3.3f]", diff.x, diff.y, diff.z);
	ofDrawBitmapString(info, 15, 15 * row, 0);

	// intersected area
	row++;
	sprintf(info, "intersect: l,t,r,b = [%3.3f,%3.3f,%3.3f,%3.3f]",
		intersect.getLeft(),
		intersect.getTop(),
		intersect.getRight(),
		intersect.getBottom());
	ofDrawBitmapString(info, 15, 15 * row, 0);

    /*
	ofSetColor(255);

	if (imageDoc1)
	{
		ofImage subImage1;
		imageDoc1->getSubImageByGlobalPosition(intersect, subImage1);
		
		row++;
		//subImage1.draw(15, 15 * count);
		subImage1.draw(15, 15 * row, 100, 100);

		//int w = max(subImage1.width, 100);
		//int h = max(subImage1.height, 100);
		//int cx = subImage1.width / 2;
		//int cy = subImage1.height / 2;
		//subImage1.drawSubsection(15, 15 * count, 100, 100, cx - w/2, cy - h/2, 100, 100);		
	}

	if (imageDoc2)
	{
		ofImage subImage2;
		imageDoc2->getSubImageByGlobalPosition(intersect, subImage2);
		
		subImage2.draw(15 + 100 + 5, 15 * row, 100, 100);
		//subImage1.saveImage("intersect.bmp", ofImageQualityType::OF_IMAGE_QUALITY_MEDIUM);
	}
    */
}

bool ImageDocumentList::loadImage(const std::string& filename)
{
	cv::Mat dummy;
	return loadImageSub(filename, dummy);
}

bool ImageDocumentList::loadImage(const cv::Mat& image)
{
	return loadImageSub("", image);
}

bool ImageDocumentList::loadImageSub(const std::string& filename, const cv::Mat& image)
{
	int count = list.size();
	int w = ofGetWidth();
	int h = ofGetHeight();

	ImageDocument* imageDoc = new ImageDocument();

	if (filename != "")
		imageDoc->loadImage(filename);
	else
		imageDoc->loadImage(image);
	
	imageDoc->moveTo(20 * count, -20 * count);
	//imageDoc->moveTo(
	//	-imageDoc->getImageWidth() + 20 * count,
	//	/*imageDoc->getImageHeight()*/ - 20 * count);

	list.push_back(imageDoc);

	return true;
}

bool ImageDocumentList::loadImageList(const std::string& filename)
{
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if( !fs.isOpened() )
        return false;

    cv::FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != cv::FileNode::SEQ )
        return false;

    cv::FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it )
	{
		if (!loadImage((std::string)*it))
			return false;
	}

	return true;
}

//void ImageDocumentList::add(ImageDocument* imageDoc)
//{
//	list.push_back(imageDoc);
//	active1 = imageDoc;
//}

void ImageDocumentList::remove(ImageDocument* imageDoc)
{
	std::vector<ImageDocument*>::iterator itr;

	itr = std::find(list.begin(), list.end(), imageDoc);
	if (itr != list.end())
	{
		// place last position
		ImageDocument* imageDoc = *itr;

		delete imageDoc;
		list.erase(itr);

		std::vector<ImageDocument*>::reverse_iterator itr;

		for (itr = list.rbegin(); itr != list.rend(); itr++)
		{
			ImageDocument* imageDoc = *itr;
			imageDoc->setActive(ActiveType::ACTIVE_1ST);
			break;
		}
	}

}

ImageDocument* ImageDocumentList::hitTest(const ofEasyCam& cam, const ofVec2f& mouse)
{
	std::vector<ImageDocument*>::reverse_iterator itr;

	int count = 0;
	float nearest = 0;
	ImageDocument* ret = nullptr;

	// find the nearest image in the list
	for (itr = list.rbegin(), count = 0; itr != list.rend(); itr++, count++)
	{
		ImageDocument* imageDoc = *itr;
		ofVec3f pos = cam.worldToScreen(imageDoc->getPosition());

		float distance = pos.distance(mouse);
		if (count == 0 || distance < nearest)
		{
			nearest = distance;
			ret = imageDoc;
		}

		//cout << "No. " << count << " " << distance << std::endl;
	}

	// check if the nearest one is under the mouse.
	if (ret)
	{
		bool hit = ret->hitTest(cam, mouse);
		if (!hit)
			ret = nullptr;
	}

	return ret;
}

void ImageDocumentList::clear()
{
	std::vector<ImageDocument*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;
		delete imageDoc;
	}

	list.clear();
}

ImageDocument* ImageDocumentList::getActive(ActiveType active_type)
{
	std::vector<ImageDocument*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;
		if (imageDoc->getActiveType() == active_type)
			return imageDoc;
	}

	return nullptr;
}

bool ImageDocumentList::makeImageList(std::vector<cv::Mat>& imageList)
{
	std::vector<ImageDocument*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); itr++)
	{
		ImageDocument* imageDoc = *itr;
		//imageList.push_back(imageDoc->getImage());
	}

	return true;
}

void ImageDocumentList::updateImage(UpdateImageType updateType)
{
	ImageDocument *imageDoc1 = getActive(ActiveType::ACTIVE_1ST);
	ImageDocument *imageDoc2 = getActive(ActiveType::ACTIVE_2ND);

	// draw intersection
	if (imageDoc1 == nullptr || imageDoc2 == nullptr)
	{
		return;
	}

	// just updating intersection
	if (updateType == kUpdateIntersectionOnly)
	{
		intersect.width = intersect.height = 0;
		intersectImage.clear();
		return;
	}

	ofRectangle rect1, rect2;
	ofImage subImage1;
	ofImage subImage2;
	cv::Mat src1;
	cv::Mat src2;

	rect1 = imageDoc1->getRect();
	rect2 = imageDoc2->getRect();
	intersect = rect1.getIntersection(rect2);
	imageDoc1->getSubImageByGlobalPosition(intersect, subImage1);
	imageDoc2->getSubImageByGlobalPosition(intersect, subImage2);

	if (subImage1.getImageType() != subImage2.getImageType())
	{
		cout << "Bpp mismatch" << std::endl;
		return;
	}

	// making images for processing
    if (subImage1.getImageType() == ofImageType::OF_IMAGE_COLOR)
	{
		src1 = cv::Mat(subImage1.getHeight(), subImage1.getWidth(), CV_8UC3, subImage1.getPixels().getData());
	}
    else if (subImage1.getImageType() == ofImageType::OF_IMAGE_GRAYSCALE)
	{
		src1 = cv::Mat(subImage1.getHeight(), subImage1.getWidth(), CV_8UC1, subImage1.getPixels().getData());
	}
	else
	{
		cout << "Unknown image type" << std::endl;
		return;
	}

    if (subImage2.getImageType() == ofImageType::OF_IMAGE_COLOR)
	{
		src2 = cv::Mat(subImage2.getHeight(), subImage2.getWidth(), CV_8UC3, subImage2.getPixels().getData());
	}
    else if (subImage2.getImageType() == ofImageType::OF_IMAGE_GRAYSCALE)
	{
		src2 = cv::Mat(subImage2.getHeight(), subImage2.getWidth(), CV_8UC1, subImage2.getPixels().getData());
	}
	else
	{
		cout << "Unknown image type" << std::endl;
		return;
	}

	cv::Mat dst;
    
    if (processing_type_ == kBlending)
        drawForBlending(src1, src2, dst);
    else if (processing_type_ == kCutting)
        drawForCutting(src1, src2, dst);

    if (subImage1.getImageType() == ofImageType::OF_IMAGE_COLOR)
	{
		subImage1.setFromPixels(dst.data, dst.cols, dst.rows, ofImageType::OF_IMAGE_COLOR);
	}
	else
	{
        subImage1.setFromPixels(dst.data, dst.cols, dst.rows, ofImageType::OF_IMAGE_GRAYSCALE);
	}

	intersectImage = subImage1;
}

void ImageDocumentList::drawForBlending(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst)
{
	if (blendingParams.type == kArithmeticAdd)
	{
		dst = src1 + src2;
	}
	else if (blendingParams.type == kArithmeticSubtract)
	{
		dst = src1 - src2;
	}
	else if (blendingParams.type == kArithmeticAlphaBlend)
	{
		double alpha = blendingParams.alpha;
		cv::addWeighted(src1, alpha, src2, 1.0 - alpha, 0, dst); 
	}
	else if (blendingParams.type == kArithmeticRampImage)
	{
		const int width = 100;
		float a = 1.0f / (blendingParams.rampEnd - blendingParams.rampStart);
		float step = 0.0f;
		cv::Mat temp(1, width, CV_32F);
			
		for (int c = 0; c < width; c++)
		{
			if (c < blendingParams.rampStart)
			{
				temp.at<float>(0, c) = 0.0f;
			}
			else if (c > blendingParams.rampEnd)
			{
				temp.at<float>(0, c) = 1.0f;
			}
			else
			{
				temp.at<float>(0, c) = a * step;
				step += 1.0f;
			}
		}

		cv::resize(temp, rampImage2, src2.size());
		//cv::imwrite("ramp2.png", rampImage2);

		dst = cv::Mat::zeros(src2.size(), src2.type());

		float* ramp_ptr = nullptr;
		unsigned char* src_ptr = nullptr;
		unsigned char* dst_ptr = nullptr;

		ramp_ptr = (float*)rampImage2.data;
		src_ptr  = (unsigned char*)src2.data;
		dst_ptr  = (unsigned char*)dst.data;

		int channels = src2.channels();

		for (int r = 0; r < src2.rows; r++)
		{
			for (int c = 0; c < src2.cols; c++)
			{
				for (int ch = 0; ch < channels; ch++)
				{
					float val = (*ramp_ptr) * static_cast<float>(*src_ptr);
					*dst_ptr = cv::saturate_cast<unsigned char>(val);
					src_ptr++;
					dst_ptr++;
				}
				ramp_ptr++;
			}
		}

		cv::flip(rampImage2, rampImage1, 1);
		//cv::imwrite("ramp1.png", rampImage2);

		ramp_ptr = (float*)rampImage1.data;
		src_ptr  = (unsigned char*)src1.data;
		dst_ptr  = (unsigned char*)dst.data;

		for (int r = 0; r < src1.rows; r++)
		{
			for (int c = 0; c < src1.cols; c++)
			{
				for (int ch = 0; ch < channels; ch++)
				{
					float val = (*ramp_ptr) * static_cast<float>(*src_ptr);
					float val2 = static_cast<float>(*dst_ptr);
					if (val + val2 > 255.0f)
						*dst_ptr = 255;
					else
						*dst_ptr += cv::saturate_cast<unsigned char>(val);
					src_ptr++;
					dst_ptr++;
				}
				ramp_ptr++;
			}
		}

	}
}

template <class T>
struct ValueIndex
{
	T value;
	int index;
};

template <class T>
bool operator<(const ValueIndex<T>& left, const ValueIndex<T>& right)
{
	return left.value < right.value;
}

void ImageDocumentList::drawForCutting(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst)
{
	cv::Mat src1_gray;
	cv::Mat src2_gray;
	cv::Mat src1_grayf;
	cv::Mat src2_grayf;
	cv::Mat diff;

    cv::cvtColor(src1, src1_gray, CV_BGR2GRAY);
    cv::cvtColor(src2, src2_gray, CV_BGR2GRAY);
	// need to be float to calculate negative value.
	src1_gray.convertTo(src1_grayf, CV_32F);
	src2_gray.convertTo(src2_grayf, CV_32F);

	//diff = src1_gray - src2_gray;
    cv::subtract(src1_grayf, src2_grayf, diff);
    cv::multiply(diff, diff, diff);
	//ofstream dump1("src1-gray.csv");
	//ofstream dump2("src2-gray.csv");
	//ofstream dump3("diff.csv");
	//dump1 << src1_gray << std::endl;
	//dump2 << src2_gray << std::endl;
	//dump3 << diff << std::endl;
	
	cv::Mat error = diff.clone();
	std::vector<cv::Point> min_points;

	// This is the way described in the paper
	// "Image Quilting for Texture Synthesis and Transfer"
	// My implementation is missing something and it doesn't work as described.
	//
#if 1
    for (int r = 1; r < diff.rows; r++) {
		for (int c = 1; c < diff.cols - 1; c++) {
			float e1 = error.at<float>(r - 1, c - 1);
			float e2 = error.at<float>(r - 1, c);
			float e3 = error.at<float>(r - 1, c + 1);
			float min_val = std::min(std::min(e1, e2), e3);
			error.at<float>(r, c) = diff.at<float>(r, c) + min_val;
		}
	}

	for (int r = 0; r < error.rows; r++) {
		double min_val, max_val;
		cv::Point min_loc, max_loc;
		cv::Mat row = error.row(r);
		cv::minMaxLoc(row, &min_val, &max_val, &min_loc);
		min_points.push_back(cv::Point(min_loc.x, r));
	}
		
#else
	cv::Point last_min;

    for (int r = 0; r < error.rows; r++) {
		if (r == 0) {
			double min_val, max_val;
			cv::Point min_loc, max_loc;
			cv::Mat row = error.row(r);
			cv::minMaxLoc(row, &min_val, &max_val, &min_loc);
			last_min = cv::Point(min_loc.x, r);
		} else {
			std::vector<ValueIndex<float> > error_values;

			const int kRange = 1;

			for (int i = -kRange; i <= kRange; i++) {
				ValueIndex<float> e;
				int c = last_min.x + i;
				c = std::max(c, 0);
				c = std::min(c, error.cols - 1);
				e.value = error.at<float>(r, c);
				e.index = c;
				error_values.push_back(e);
			}

			std::sort(error_values.begin(), error_values.end());

			last_min.x = error_values[0].index;
			last_min.y = r;
		}

		last_min.x = std::max(last_min.x, 1);
		last_min.x = std::min(last_min.x, error.cols - 2);

		min_points.push_back(last_min);
	}
#endif
    
	// Make overlayed image from 2 images
	int count = 0;
    cv::Point pt0, pt1, pt2;
    cv::Scalar color(255, 255, 255);
    cv::Mat mask = cv::Mat::zeros(src1.rows, src1.cols, CV_8U);
    
    std::vector<cv::Point>::iterator itr;
    for (itr = min_points.begin(); itr != min_points.end(); itr++) {
        pt0 = pt1 = *itr;
        pt0.x = 0;
        cv::line(mask, pt0, pt1, color);
    }
    
    src1.copyTo(dst, mask);
    cv::bitwise_not(mask, mask);
    src2.copyTo(dst, mask);

#if 0
    for (itr = min_points.begin(); itr != min_points.end(); itr++) {
        if (count == 0) {
            pt1 = *itr;
            count++;
            continue;
        }
        
        pt2 = *itr;
        cv::line(dst, pt1, pt2, color);
        pt1 = pt2;
        count++;
    }
#endif

}
