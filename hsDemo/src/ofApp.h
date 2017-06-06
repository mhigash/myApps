#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "MeasurementDataSet.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	void processOpenFileSelection(ofFileDialogResult openFileResult);

	ofEasyCam cam;

	bool bHide;

	ofxColorSlider color;
	ofxPanel gui;

	ofImage currentImage;
	ofPoint mouse;
	
	std::vector<ofImage> images;

	MeasurementDataSet measurement;
	HsImageDataType currentImageType;
	HsImageColorType currentColorType;
	HsColorSetting currentColorSetting;

	ofParameterGroup parameters;
	ofParameter<bool> showTristimulusX;
	ofParameter<bool> showTristimulusY;
	ofParameter<bool> showTristimulusZ;
	ofParameter<bool> showChromaticityX;
	ofParameter<bool> showChromaticityY;
	ofParameter<bool> showChromaticityU;
	ofParameter<bool> showChromaticityV;
	ofParameter<bool> showLabL;
	ofParameter<bool> showLabA;
	ofParameter<bool> showLabB;
	ofParameter<bool> showRgb;
	ofParameter<bool> showSpectralRadiance;
	ofParameter<int> wavelength;

	void resetImageType();
	void showTristimulusXChanged(bool& show);
	void showTristimulusYChanged(bool& show);
	void showTristimulusZChanged(bool& show);
	void showChromaticityXChanged(bool& show);
	void showChromaticityYChanged(bool& show);
	void showChromaticityUChanged(bool& show);
	void showChromaticityVChanged(bool& show);
	void showLabLChanged(bool& show);
	void showLabAChanged(bool& show);
	void showLabBChanged(bool& show);
	void showRgbChanged(bool& show);
	void showSpectralRadianceChanged(bool& show);
	void wavelengthChanged(int& wavlength);

	void updateCurrentImage();

	ofParameterGroup colors;
	ofParameter<bool> showColorPseudo;
	ofParameter<bool> showColorPseudoContour;
	ofParameter<bool> showColorGrayscale;
	ofParameter<bool> showColorGrayscaleContour;
	ofParameter<bool> showColorRGB;

	void resetColorType();
	void showColorPseudoChanged(bool& show);
	void showColorPseudoContourChanged(bool& show);
	void showColorGrayscaleChanged(bool& show);
	void showColorGrayscaleContourChanged(bool& show);
	void showColorRGBChanged(bool& show);

	ofParameterGroup views;
	ofParameter<bool> showHistogram;
	ofParameter<bool> showPixelData;

	std::vector<int> histogram;
	int histogram_max;
	int histogram_min;
	int histogram_total;

	HsPixelData pixelData;
};
