#include "image_document.h"


ImageDocument::ImageDocument(void)
	:active_type(ACTIVE_NONE)
{
}


ImageDocument::~ImageDocument(void)
{
}

void ImageDocument::setup()
{
}

void ImageDocument::update()
{
}

void ImageDocument::draw()
{
	// draw image
	ofSetColor(255);

#if 0
	image.draw(location.x, location.y);

	//for( int i = 0; i < corners.size(); i++ ) {
	//	ofRectangle(corners[i].x, corners[i].y, 5, 5);
	//}

#else
	image.bind();
	ofFill();
	// draw image
	ofSetColor(255);
	ofDrawPlane(location, image.getWidth(), -image.getHeight());
	image.unbind();

	for( int i = 0; i < corners.size(); i++ ) {
		ofPoint pt;
		pt.z = location.z + 1;
		pt.x = location.x + corners[i].x - image.getWidth() / 2;
		pt.y = location.y + image.getHeight() - corners[i].y - image.getHeight() / 2;
		ofDrawPlane(pt, 5, 5);
	}

	if (active_type == ActiveType::ACTIVE_1ST) {
		ofSetColor(255, 0, 0);
		ofDrawPlane(location, image.getWidth() + 10, -(image.getHeight() + 10));
	} else if (active_type == ActiveType::ACTIVE_2ND) {
		ofSetColor(0, 0, 255);
		ofDrawPlane(location, image.getWidth() + 10, -(image.getHeight() + 10));
	}
	
#endif

}

void ImageDocument::moveTo(int x, int y)
{
	location.x = x;
	location.y = y;

	updateRect();
}

void ImageDocument::offset(int x, int y)
{
	location.x += x;
	location.y += y;

	updateRect();
}

bool ImageDocument::loadImage(const std::string& filename)
{
	//image = cv::imread(filename);

	//cv::Mat imageToShow;
	//cout << "depth: " << image.depth() << ", channels: " << image.channels() << endl;
	//cv::cvtColor(image, imageToShow, CV_BGR2RGB);

	//colorImg.allocate(imageToShow.cols, imageToShow.rows);
	//colorImg.setFromPixels(imageToShow.data, imageToShow.cols, imageToShow.rows);

	int extention_position = filename.rfind('.');
	std::string extention = filename.substr(extention_position + 1);

	extention = ofToLower(extention);

	if (extention == "png" || extention == "jpg" || extention == "bmp") {
		image.load(filename);
	} else {
		return false;
	}

	return true;
}

bool ImageDocument::loadImage(const cv::Mat& newImage)
{
	//image = newImage.clone();

	//cv::Mat imageToShow;
	//cout << "depth: " << image.depth() << ", channels: " << image.channels() << endl;
	//if (image.channels() == 1) {
	//	cv::cvtColor(image, imageToShow, CV_GRAY2RGB);
	//} else {
	//	cv::cvtColor(image, imageToShow, CV_BGR2RGB);
	//}

	//colorImg.allocate(imageToShow.cols, imageToShow.rows);
	//colorImg.setFromPixels(imageToShow.data, imageToShow.cols, imageToShow.rows);

	return true;
}

void ImageDocument::test()
{
	//image.getPixels();
	cv::Mat image_gray;
	cv::Mat image_color;

    if (image.getImageType() == ofImageType::OF_IMAGE_COLOR) {
		image_color = cv::Mat(image.getHeight(), image.getWidth(), CV_8UC3, image.getPixels().getData());
		cv::cvtColor(image_color, image_gray, CV_RGB2GRAY);
    } else if (image.getImageType() == ofImageType::OF_IMAGE_GRAYSCALE){
		image_gray = cv::Mat(image.getHeight(), image.getWidth(), CV_8UC1, image.getPixels().getData());
		image_color = image_gray;
	} else {
		cout << "Unknown image type" << std::endl;
	}
	
	using namespace cv;

	int processing = 1;

	if (processing == 0) {
		corners.clear();
		int maxCorners = 100;
		double qualityLevel = 0.01;
		double minDistance = 10;
		int blockSize = 3;
		bool useHarrisDetector = false;
		double k = 0.04;

		/// Apply corner detection
		goodFeaturesToTrack(image_gray,
					corners,
					maxCorners,
					qualityLevel,
					minDistance,
					Mat(),
					blockSize,
					useHarrisDetector,
					k );

		/// Draw corners detected
		cout << "** Number of corners detected: "<< corners.size() << endl;
	} else if (processing == 1) {
	
		float kernel_values[] = {
			-1, 0, 1,
			-2, 0, 2,
			-1, 0, 1,
		};

		Mat kernel = Mat(3, 3, CV_32F, kernel_values).clone();
		
		kernel /= 8;

		filter2D(image_color, image_color, image_color.depth(), kernel);

        if (image.getImageType() == ofImageType::OF_IMAGE_COLOR) {
			image.setFromPixels(image_color.data, image_color.cols, image_color.rows, ofImageType::OF_IMAGE_COLOR);
		} else {
			image.setFromPixels(image_color.data, image_color.cols, image_color.rows, ofImageType::OF_IMAGE_GRAYSCALE);
		}
	}
}

void ImageDocument::setActive(ActiveType new_active_type)
{
	active_type = new_active_type;
	if (active_type == ActiveType::ACTIVE_1ST)
		location.z = 2;
	else if (active_type == ActiveType::ACTIVE_2ND)
		location.z = 1;
	else
		location.z = 0;
}

bool ImageDocument::hitTest(const ofEasyCam& cam, const ofVec2f& mouse)
{
	ofVec3f topRight(
		location.x + image.getWidth() / 2,
		location.y + image.getHeight() / 2);
	ofVec3f bottomLeft(
		location.x - image.getWidth() / 2,
		location.y - image.getHeight() / 2);

	topRight = cam.worldToScreen(topRight);
	bottomLeft = cam.worldToScreen(bottomLeft);

	ofRectangle rect(bottomLeft, topRight);
	
	return rect.inside(mouse);
}

bool ImageDocument::getSubImage(const ofEasyCam& cam, const ofVec2f& mouse, ofImage& subImage)
{
	return false;
}

void ImageDocument::updateRect()
{
	rect.setFromCenter(location, image.getWidth(), image.getHeight());
}

bool ImageDocument::getSubImageByGlobalPosition(ofRectangle globalRect, ofImage& subImage)
{
	float left   = globalRect.getLeft();
	//float top    = globalRect.getTop();
	float top    = globalRect.getBottom();// bottom has bigger value. inverted?
	float right  = globalRect.getRight();
	float bottom = globalRect.getBottom();

	float left2  = rect.getLeft();
	//float top2   = rect.getTop();
	float top2   = rect.getBottom();// bottom has bigger value. inverted?

	int x = static_cast<int>(left - left2);
	int y = static_cast<int>(-(top - top2));
	int w = static_cast<int>(globalRect.getWidth());
	int h = static_cast<int>(abs(globalRect.getHeight()));

    if (w <= 0 || h <= 0)
        return false;
    
	//subImage = image;
	//subImage.crop(x, y, w, h);
	subImage.cropFrom(image, x, y, w, h);
	
	return true;
}

