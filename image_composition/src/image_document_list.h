#pragma once

#include "image_document.h"

enum ProcessingType
{
    kBlending,
    kCutting,
};

enum ArithmeticType
{
    kArithmeticNone,
    kArithmeticAdd,
    kArithmeticSubtract,
    kArithmeticAlphaBlend,
    kArithmeticRampImage,
};

enum CuttingType
{
    kCutting1,
    kCutting2,
};

enum UpdateImageType
{
	kUpdateAll,
	kUpdateIntersectionOnly,
};

struct BlendingParams
{
	ArithmeticType type;
	float alpha;
	float rampStart;
	float rampEnd;
};

struct CuttingParams
{
    CuttingType type;
    int range;
    bool showLines;
};

class ImageDocumentList
{
	std::vector<ImageDocument*> list;

	ofRectangle intersect;

    ProcessingType processingType;

	BlendingParams blendingParams;
	cv::Mat rampImage1;
	cv::Mat rampImage2;

	ofImage intersectImage;
    
	CuttingParams cuttingParams;

	void clear();

	bool loadImageSub(const std::string& filename, const cv::Mat& image);
	bool makeImageList(std::vector<cv::Mat>& imageList);
public:

	ImageDocumentList(void);
	~ImageDocumentList(void);

	bool loadImage(const std::string& filename);
	bool loadImage(const cv::Mat& image);
	bool loadImageList(const std::string& filename);

	void setup();
	void update();
	void draw();
	void drawInfo();
	//void add(ImageDocument* imageDoc);
	void remove(ImageDocument* imageDoc);

	ImageDocument* hitTest(const ofEasyCam& cam, const ofVec2f& mouse);
	ImageDocument* getActive(ActiveType active_type);

    ProcessingType getProcessingType() { return processingType; }
    void setProcessingType(ProcessingType processing_type) { processingType = processing_type; }

	BlendingParams getArithmeticParams() { return blendingParams; }
	void setBlendingParams(BlendingParams params) { blendingParams = params; }

	CuttingParams getCuttingParams() { return cuttingParams; }
	void setCuttingParams(CuttingParams params) { cuttingParams = params; }

	void updateImage(UpdateImageType updateType);

    void drawForBlending(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);
    void drawForCutting(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);
};

