#pragma once

#include "ofxOpenCv.h"

typedef enum _ActiveType
{
	ACTIVE_NONE,
	ACTIVE_1ST,
	ACTIVE_2ND,
} ActiveType;

class ImageDocument
{
    //ofxCvColorImage	colorImg;
	ofVec3f location;
	ofImage image;

	cv::vector<cv::KeyPoint> keypoints;

	std::vector<cv::Point2f> corners;
	ActiveType active_type;

	ofRectangle rect;

	void updateRect();
public:

	ImageDocument(void);
	~ImageDocument(void);

	void setup();
	void update();
	void draw();
	void moveTo(int x, int y);
	void offset(int x, int y);
	void test();

	bool loadImage(const std::string& filename);
	bool loadImage(const cv::Mat& newImage);

	int getImageWidth()
	{
		return image.getWidth();
	}

	int getImageHeight()
	{
		return image.getHeight();
	}

	ofVec3f getPosition()
	{
		return location;
	}

	ofRectangle getRect()
	{
		return rect;
	}

	ActiveType getActiveType()
	{
		return active_type;
	}

	void setActive(ActiveType new_active_type);

	bool hitTest(const ofEasyCam& cam, const ofVec2f& mouse);
	bool getSubImage(const ofEasyCam& cam, const ofVec2f& mouse, ofImage& subImage);
	bool getSubImageByGlobalPosition(ofRectangle rect, ofImage& subImage);
};

