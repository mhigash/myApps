#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.disableMouseInput();

	cam.setDistance(1000);

	ofSetVerticalSync(true);

	gui.setup();

	arithmeticGui.setup("Arithmetics");
	arithmeticGui.add(arithmeticAdd.set("add", false, false, true));
	arithmeticGui.add(arithmeticSubtract.set("subtract", false, false, true));
	arithmeticGui.add(arithmeticAlphaBlending.set("alpha", false, false, true));
	arithmeticGui.add(arithmeticAlpha.setup("alpha", 0.5, 0.0, 1.0));
	arithmeticGui.add(arithmeticRampImage.set("ramp image", false, false, true));
	arithmeticGui.add(arithmeticRampStart.setup("ramp start", 33, 0, 100));
	arithmeticGui.add(arithmeticRampEnd.setup("ramp end", 66, 0, 100));
	arithmeticRampStart.addListener(this, &ofApp::arithmeticRampStartChanged);
	arithmeticRampEnd.addListener(this, &ofApp::arithmeticRampEndChanged);
	resetArithmetics();
	arithmeticAlphaBlending = true;

	gui.add(&arithmeticGui);


	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	//
	// image.draw doesn't work if this is used.
	ofEnableNormalizedTexCoords();
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableDepthTest();
	ofEnableNormalizedTexCoords();

	cam.begin();

	documentList.draw();
	
	cam.end();

	ofDisableDepthTest();
	ofDisableNormalizedTexCoords();

	documentList.drawInfo();

	gui.setPosition(ofGetWidth() - gui.getWidth() - 10, gui.getPosition().y);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
	} else if (key == 'f') {
		ImageDocument* doc = documentList.getActive(ActiveType::ACTIVE_1ST);
		if (doc) {
			doc->test();
		}
	} else if (key == 'c') {
		documentList.remove(documentList.getActive(ActiveType::ACTIVE_1ST));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){



}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 
	if (!file.exists())
		return;

	//Limiting this example to one image so we delete previous ones
	//processedImages.clear();
	//loadedImages.clear();
		
	ofLogVerbose("The file exists - now checking the type via file extension");
	string fileExtension = ofToUpper(file.getExtension());
		
	if (fileExtension == "XML") {
		// image list format only.
		//documentList.loadImageList(openFileResult.getPath());
	} else {
		documentList.loadImage(openFileResult.getPath());
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//printf("dragged - %d, %d\n", x, y);

	ofPoint point;
	point.x = (x - lastX);
	point.y = (y - lastY);

	ImageDocument* active = documentList.getActive(ActiveType::ACTIVE_1ST);
	if (active){
		//imageDoc->processing();
		if (lastX != 0 && lastY != 0){
			active->offset(point.x, -point.y);
		}
	}

	lastX = x;
	lastY = y;
	documentList.updateImage(1);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofVec2f mouse(x, y);

	ImageDocument* imageDoc = documentList.hitTest(cam, mouse);
	
	if (imageDoc){
		//imageDoc->processing();
		ActiveType active_type = ActiveType::ACTIVE_NONE;

		if (button == OF_MOUSE_BUTTON_LEFT)
		{
			active_type = ActiveType::ACTIVE_1ST;
		}
		else if (button == OF_MOUSE_BUTTON_RIGHT)
		{
			active_type = ActiveType::ACTIVE_2ND;
		}

		if (active_type != ActiveType::ACTIVE_NONE)
		{
			ImageDocument* imageDocOld = documentList.getActive(active_type);
			if (imageDocOld)
				imageDocOld->setActive(ActiveType::ACTIVE_NONE);

			imageDoc->setActive(active_type);
		}
	}

	lastX = 0;
	lastY = 0;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	lastX = 0;
	lastY = 0;

	documentList.updateImage(0);
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

void ofApp::resetArithmetics()
{
	arithmeticAdd.removeListener(this, &ofApp::arithmeticAddChanged);
	arithmeticSubtract.removeListener(this, &ofApp::arithmeticSubtractChanged);
	arithmeticAlphaBlending.removeListener(this, &ofApp::arithmeticAlphaBlendingChanged);
	arithmeticRampImage.removeListener(this, &ofApp::arithmeticRampImageChanged);

	arithmeticAdd = false;
	arithmeticSubtract = false;
	arithmeticAlphaBlending = false;
	arithmeticRampImage = false;

	arithmeticAdd.addListener(this, &ofApp::arithmeticAddChanged);
	arithmeticSubtract.addListener(this, &ofApp::arithmeticSubtractChanged);
	arithmeticAlphaBlending.addListener(this, &ofApp::arithmeticAlphaBlendingChanged);
	arithmeticRampImage.addListener(this, &ofApp::arithmeticRampImageChanged);
}

void ofApp::arithmeticAddChanged(bool& show)
{
	resetArithmetics();
	arithmeticAdd = true;
	updateParameters();
}

void ofApp::arithmeticSubtractChanged(bool& show)
{
	resetArithmetics();
	arithmeticSubtract = true;
	updateParameters();
}

void ofApp::arithmeticAlphaBlendingChanged(bool& show)
{
	resetArithmetics();
	arithmeticAlphaBlending = true;
	updateParameters();
}

void ofApp::arithmeticRampImageChanged(bool& show)
{
	resetArithmetics();
	arithmeticRampImage = true;
	updateParameters();
}

void ofApp::arithmeticRampStartChanged(int& value)
{
	updateParameters();
}

void ofApp::arithmeticRampEndChanged(int& value)
{
	updateParameters();
}

void ofApp::updateParameters()
{
	if (arithmeticAdd) {
		arithmeticParams.type = kArithmeticAdd;
	} else if (arithmeticSubtract) {
		arithmeticParams.type = kArithmeticSubtract;
	} else if (arithmeticAlphaBlending) {
		arithmeticParams.type = kArithmeticAlphaBlend;
		arithmeticParams.alpha = arithmeticAlpha;
	} else if (arithmeticRampImage) {
		arithmeticParams.type = kArithmeticRampImage;
		arithmeticParams.rampStart = arithmeticRampStart;
		arithmeticParams.rampEnd = arithmeticRampEnd;
	}

	documentList.setArithmeticParams(arithmeticParams);
	
	documentList.updateImage(0);
}
