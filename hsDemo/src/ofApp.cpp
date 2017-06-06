#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	gui.setup(); // most of the time you don't need a name
	//gui.add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	
	parameters.setName("data");
	parameters.add(showTristimulusX.set("X", false, false, true));
	parameters.add(showTristimulusY.set("Y", true, false, true));
	parameters.add(showTristimulusZ.set("Z", false, false, true));
	parameters.add(showChromaticityX.set("x", false, false, true));
	parameters.add(showChromaticityY.set("y", false, false, true));
	parameters.add(showChromaticityU.set("u'", false, false, true));
	parameters.add(showChromaticityV.set("v'", false, false, true));
	parameters.add(showLabL.set("L*", false, false, true));
	parameters.add(showLabA.set("a*", false, false, true));
	parameters.add(showLabB.set("b*", false, false, true));
	parameters.add(showRgb.set("RGB", false, false, true));
	parameters.add(showSpectralRadiance.set("lambda", false, false, true));
	parameters.add(wavelength.set("wavelength", 555, 380, 780));

	resetImageType();
	showTristimulusY = true;
	currentImageType = HS_IMAGE_DATA_TYPE_TRISTIMULUS_Y;

	wavelength.addListener(this, &ofApp::wavelengthChanged);

	colors.setName("color");
	colors.add(showColorPseudo.set("pseudo", true, false, true));
	colors.add(showColorPseudoContour.set("pseudo contour", false, false, true));
	colors.add(showColorGrayscale.set("grayscale", false, false, true));
	colors.add(showColorGrayscaleContour.set("grayscale contour", false, false, true));
	colors.add(showColorRGB.set("RGB", false, false, true));

	resetColorType();
	showColorPseudo = true;
	currentColorType = HS_IMAGE_COLOR_TYPE_PSEUDO;
	
	memset(&currentColorType, 0, sizeof(currentColorType));

	views.setName("view");
	views.add(showHistogram.set("histogram", true, false, true));
	views.add(showPixelData.set("pixel", false, false, true));

	gui.add(parameters);
	gui.add(colors);
	gui.add(views);

	bHide = true;

	//cam.disableMouseInput();

	cam.setDistance(1000);

	ofSetVerticalSync(true);

	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();

	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	//
	// image.draw doesn't work if this is used.
	ofEnableNormalizedTexCoords();

	measurement.Initialize();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);

	ofEnableDepthTest();
	ofEnableNormalizedTexCoords();

	ofFill();
	// draw image
	ofSetColor(255);
		
	cam.begin();
	//documentList.draw();

	bool showSpectralImages = false;
	if (showSpectralImages) {
		const int DISTANCE_Z = 100;
		int pos_z = images.size() / 2 * DISTANCE_Z;
	
		for (std::vector<ofImage>::iterator itr = images.begin(); itr != images.end(); itr++)
		{
			ofVec3f location;
			ofImage image = *itr;

			location.z = pos_z;

			image.bind();
			ofDrawPlane(location, image.getWidth(), -image.getHeight());
			image.unbind();

			pos_z -= DISTANCE_Z;
		}
	} else {
		ofVec3f location;

		currentImage.bind();
		ofDrawPlane(location, currentImage.getWidth(), -currentImage.getHeight());
		currentImage.unbind();
	}

	cam.end();
	
	ofDisableDepthTest();
	ofDisableNormalizedTexCoords();

	if (showHistogram && histogram.size() > 0) {
		float height = 100;
		ofPoint offset(10, 10);
	
		ofPoint p1(offset.x, offset.y + height);
		ofPoint p2(offset.x, offset.y + height);
		ofPoint p3(offset.x, offset.y + height);
		ofPoint p4(offset.x, offset.y + height);

		int color = 0;
		int cumulative = 0;

		ofSetColor(ofColor(0, 128, 128));
		ofRect(offset, histogram.size(), height);
		
		for (std::vector<int>::iterator itr = histogram.begin(); itr != histogram.end(); itr++) {
			int count = *itr;
			cumulative += count;

			// draw histogram
			float ratio = (count - histogram_min) / float(histogram_max - histogram_min);

			p1.x += 1;
			p2.x += 1;
			p3.x += 1;

			p2.y = offset.y + height - height * ratio;

			ofSetColor(color++);
			ofLine(p1, p2);

			// draw cumulative line
			ratio = float(cumulative) / float(histogram_total);
			p3.y = offset.y + height - height * ratio;
			
			ofSetColor(255);
			ofLine(p3, p4);

			p4 = p3;
		}
	}

	if (showPixelData && histogram.size() > 0) {
	}

	// auto draw?
	// should the gui control hiding?
	if( bHide ){
		// rightening
		gui.setPosition(ofGetWidth() - gui.getWidth() - 10, gui.getPosition().y);
		gui.draw();
	}

	ofVec3f before(mouse);
	ofVec3f after = cam.screenToWorld(before);

	std::stringstream text;
	text << "[" << mouse.x << "," << mouse.y << "] --> [" << after.x << "," << after.y << "]";
	ofDrawBitmapString(text.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//if( key == 'h' ){
	//	bHide = !bHide;
	//}
	//if(key == 's') {
	//	gui.saveToFile("settings.xml");
	//}
	//if(key == 'l') {
	//	gui.loadFromFile("settings.xml");
	//}

	if(key == ' '){
		//color = ofColor(255);
	
		//Open the Open File Dialog
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png"); 
		
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			ofLogVerbose("User selected a file");
			
			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);
			
		}else {
			ofLogVerbose("User hit cancel");
		}
	} else if (key == '0') {
		cam.reset();
		//cam.setScale(1, 1, 1);
	} else if (key == 'j') {
		cam.move(0, -100, 0);
	} else if (key == 'k') {
		cam.move(0, 100, 0);
	} else if (key == 'h') {
		cam.move(100, 0, 0);
	} else if (key == 'l') {
		cam.move(-100, 0, 0);
	} else if (key == 'u') {
		cam.dolly(100);
	} else if (key == 'i') {
		cam.dolly(-100);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouse.x = x;
	mouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 
	if (!file.exists()) return;
	
	ofLogVerbose("The file exists - now checking the type via file extension");
	string fileExtension = ofToUpper(file.getExtension());
		
	if (fileExtension == "HSM") {
		HsError ret = measurement.Load(openFileResult.getPath());
		if (ret != HS_ERROR_NONE) return;

		images.clear();

		for (int wavlen = 380, count = 0; wavlen < 780; wavlen += 10, count++) {
			ofImage image1;
			ret = measurement.GetImage(HsImageDataType::HS_IMAGE_DATA_TYPE_SPECTRAL_RADIANCE, wavlen, image1);
	
			if (ret != HS_ERROR_NONE) continue;

			images.push_back(image1);
		}

		updateCurrentImage();
	}
}

void ofApp::resetImageType()
{
	showTristimulusX.removeListener(this, &ofApp::showTristimulusXChanged);
	showTristimulusY.removeListener(this, &ofApp::showTristimulusYChanged);
	showTristimulusZ.removeListener(this, &ofApp::showTristimulusZChanged);
	showChromaticityX.removeListener(this, &ofApp::showChromaticityXChanged);
	showChromaticityY.removeListener(this, &ofApp::showChromaticityYChanged);
	showChromaticityU.removeListener(this, &ofApp::showChromaticityUChanged);
	showChromaticityV.removeListener(this, &ofApp::showChromaticityVChanged);
	showLabL.removeListener(this, &ofApp::showLabLChanged);
	showLabA.removeListener(this, &ofApp::showLabAChanged);
	showLabB.removeListener(this, &ofApp::showLabBChanged);
	showRgb.removeListener(this, &ofApp::showRgbChanged);
	showSpectralRadiance.removeListener(this, &ofApp::showSpectralRadianceChanged);

	showTristimulusX = false;
	showTristimulusY = false;
	showTristimulusZ = false;
	showChromaticityX = false;
	showChromaticityY = false;
	showChromaticityU = false;
	showChromaticityV = false;
	showLabL = false;
	showLabA = false;
	showLabB = false;
	showRgb = false;
	showSpectralRadiance = false;

	showTristimulusX.addListener(this, &ofApp::showTristimulusXChanged);
	showTristimulusY.addListener(this, &ofApp::showTristimulusYChanged);
	showTristimulusZ.addListener(this, &ofApp::showTristimulusZChanged);
	showChromaticityX.addListener(this, &ofApp::showChromaticityXChanged);
	showChromaticityY.addListener(this, &ofApp::showChromaticityYChanged);
	showChromaticityU.addListener(this, &ofApp::showChromaticityUChanged);
	showChromaticityV.addListener(this, &ofApp::showChromaticityVChanged);
	showLabL.addListener(this, &ofApp::showLabLChanged);
	showLabA.addListener(this, &ofApp::showLabAChanged);
	showLabB.addListener(this, &ofApp::showLabBChanged);
	showRgb.addListener(this, &ofApp::showRgbChanged);
	showSpectralRadiance.addListener(this, &ofApp::showSpectralRadianceChanged);
}

void ofApp::showTristimulusXChanged(bool& show){
	resetImageType();
	showTristimulusX = true;
	updateCurrentImage();
}

void ofApp::showTristimulusYChanged(bool& show){
	resetImageType();
	showTristimulusY = true;
	updateCurrentImage();
}

void ofApp::showTristimulusZChanged(bool& show){
	resetImageType();
	showTristimulusZ = true;
	updateCurrentImage();
}

void ofApp::showChromaticityXChanged(bool& show){
	resetImageType();
	showChromaticityX = true;
	updateCurrentImage();
}

void ofApp::showChromaticityYChanged(bool& show){
	resetImageType();
	showChromaticityY = true;
	updateCurrentImage();
}

void ofApp::showChromaticityUChanged(bool& show){
	resetImageType();
	showChromaticityU = true;
	updateCurrentImage();
}

void ofApp::showChromaticityVChanged(bool& show){
	resetImageType();
	showChromaticityV = true;
	updateCurrentImage();
}

void ofApp::showLabLChanged(bool& show){
	resetImageType();
	showLabL = true;
	updateCurrentImage();
}

void ofApp::showLabAChanged(bool& show){
	resetImageType();
	showLabA = true;
	updateCurrentImage();
}

void ofApp::showLabBChanged(bool& show){
	resetImageType();
	showLabB = true;
	updateCurrentImage();
}

void ofApp::showRgbChanged(bool& show){
	resetImageType();
	showRgb = true;
	updateCurrentImage();
}

void ofApp::showSpectralRadianceChanged(bool& show){
	resetImageType();
	showSpectralRadiance = true;
	updateCurrentImage();
}

void ofApp::wavelengthChanged(int& wavlength)
{
	if (showSpectralRadiance) {
		updateCurrentImage();
	}
}

void ofApp::updateCurrentImage()
{
	if (showTristimulusX)
		currentImageType = HS_IMAGE_DATA_TYPE_TRISTIMULUS_X;
	else if (showTristimulusY)
		currentImageType = HS_IMAGE_DATA_TYPE_TRISTIMULUS_Y;
	else if (showTristimulusZ)
		currentImageType = HS_IMAGE_DATA_TYPE_TRISTIMULUS_Z;
	else if (showChromaticityX)
		currentImageType = HS_IMAGE_DATA_TYPE_CHROMATICITY_X;
	else if (showChromaticityY)
		currentImageType = HS_IMAGE_DATA_TYPE_CHROMATICITY_Y;
	else if (showChromaticityU)
		currentImageType = HS_IMAGE_DATA_TYPE_CHROMATICITY_U;
	else if (showChromaticityV)
		currentImageType = HS_IMAGE_DATA_TYPE_CHROMATICITY_V;
	else if (showLabL)
		currentImageType = HS_IMAGE_DATA_TYPE_LAB_L;
	else if (showLabA)
		currentImageType = HS_IMAGE_DATA_TYPE_LAB_A;
	else if (showLabB)
		currentImageType = HS_IMAGE_DATA_TYPE_LAB_B;
	else if (showRgb)
		currentImageType = HS_IMAGE_DATA_TYPE_RGB;
	else if (showSpectralRadiance)
		currentImageType = HS_IMAGE_DATA_TYPE_SPECTRAL_RADIANCE;

	if (showColorPseudo)
		currentColorType = HS_IMAGE_COLOR_TYPE_PSEUDO;
	else if (showColorPseudoContour)
		currentColorType = HS_IMAGE_COLOR_TYPE_PSEUDO;
	else if (showColorGrayscale)
		currentColorType = HS_IMAGE_COLOR_TYPE_PSEUDO;
	else if (showColorGrayscaleContour)
		currentColorType = HS_IMAGE_COLOR_TYPE_PSEUDO;
	else if (showColorRGB)
		currentColorType = HS_IMAGE_COLOR_TYPE_RGB;

	HsError ret = measurement.GetImage(currentImageType, wavelength, currentImage);
	if (ret != HS_ERROR_NONE)
		return;

	if (showHistogram) {
		ret = measurement.GetHistogram(currentImageType, 255, histogram);

		if (ret == HS_ERROR_NONE) {
			std::vector<int>::iterator itrMaxVal = std::max_element(histogram.begin(), histogram.end());
			histogram_max = *itrMaxVal;
			histogram_min = 0;
			histogram_total = std::accumulate(histogram.begin(), histogram.end(), 0);
		}
	}
}

void ofApp::resetColorType()
{
	showColorPseudo.removeListener(this, &ofApp::showColorPseudoChanged);
	showColorPseudoContour.removeListener(this, &ofApp::showColorPseudoContourChanged);
	showColorGrayscale.removeListener(this, &ofApp::showColorGrayscaleChanged);
	showColorGrayscaleContour.removeListener(this, &ofApp::showColorGrayscaleContourChanged);
	showColorRGB.removeListener(this, &ofApp::showColorRGBChanged);

	showColorPseudo = false;
	showColorPseudoContour = false;
	showColorGrayscale = false;
	showColorGrayscaleContour = false;
	showColorRGB = false;

	showColorPseudo.addListener(this, &ofApp::showColorPseudoChanged);
	showColorPseudoContour.addListener(this, &ofApp::showColorPseudoContourChanged);
	showColorGrayscale.addListener(this, &ofApp::showColorGrayscaleChanged);
	showColorGrayscaleContour.addListener(this, &ofApp::showColorGrayscaleContourChanged);
	showColorRGB.addListener(this, &ofApp::showColorRGBChanged);
}

void ofApp::showColorPseudoChanged(bool& show)
{
	resetColorType();
	showColorPseudo = true;
	updateCurrentImage();
}

void ofApp::showColorPseudoContourChanged(bool& show)
{
	resetColorType();
	showColorPseudoContour = true;
	updateCurrentImage();
}

void ofApp::showColorGrayscaleChanged(bool& show)
{
	resetColorType();
	showColorGrayscale = true;
	updateCurrentImage();
}

void ofApp::showColorGrayscaleContourChanged(bool& show)
{
	resetColorType();
	showColorGrayscaleContour = true;
	updateCurrentImage();
}

void ofApp::showColorRGBChanged(bool& show)
{
	resetColorType();
	showColorRGB = true;
	updateCurrentImage();
}

