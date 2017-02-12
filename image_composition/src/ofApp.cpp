#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.disableMouseInput();

	cam.setDistance(1000);

	ofSetVerticalSync(true);

	gui.setup();
    
    typeGui.setup();
    typeGui.setName("type");
    typeGui.add(typeBlending.set("blending", false, false, true));
    typeGui.add(typeCutting.set("cutting", false, false, true));
    
    typeBlending.addListener(this, &ofApp::typeBlendingChanged);
    typeCutting.addListener(this, &ofApp::typeCuttingChanged);
    resetTypes();
    typeBlending = true;
    
    gui.add(&typeGui);
    
    blendingGui.setup();
	blendingGui.setName("blending");
	blendingGui.add(blendingAdd.set("add", false, false, true));
	blendingGui.add(blendingSubtract.set("subtract", false, false, true));
	blendingGui.add(blendingAlphaBlending.set("alpha blending", false, false, true));
	blendingGui.add(blendingAlpha.setup("alpha", 0.5, 0.0, 1.0));
	blendingGui.add(blendingRampImage.set("ramp image", false, false, true));
	blendingGui.add(blendingRampStart.setup("ramp start", 33, 0, 100));
	blendingGui.add(blendingRampEnd.setup("ramp end", 66, 0, 100));
	
    blendingRampStart.addListener(this, &ofApp::blendingRampStartChanged);
	blendingRampEnd.addListener(this, &ofApp::blendingRampEndChanged);	
    resetBlendings();
	blendingAlphaBlending = true;

	gui.add(&blendingGui);

    cuttingGui.setup();
    cuttingGui.setName("cutting");

    gui.add(&cuttingGui);
    
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
	
	if (blendingRampImage) {
		// because it's slow
		documentList.updateImage(UpdateImageType::kUpdateIntersectionOnly);
	} else {
		documentList.updateImage(UpdateImageType::kUpdateAll);
	}
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

	documentList.updateImage(UpdateImageType::kUpdateAll);
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

void ofApp::resetTypes() {
    typeBlending.removeListener(this, &ofApp::typeBlendingChanged);
    typeCutting.removeListener(this, &ofApp::typeCuttingChanged);
    
    typeBlending = false;
    typeCutting = false;
    
    typeBlending.addListener(this, &ofApp::typeBlendingChanged);
    typeCutting.addListener(this, &ofApp::typeCuttingChanged);
}

void ofApp::typeBlendingChanged(bool& show)
{
    resetTypes();
    typeBlending = true;
    updateParameters();
}

void ofApp::typeCuttingChanged(bool& show)
{
    resetTypes();
    typeCutting = true;
    updateParameters();
}

void ofApp::resetBlendings()
{
	blendingAdd.removeListener(this, &ofApp::blendingAddChanged);
	blendingSubtract.removeListener(this, &ofApp::blendingSubtractChanged);
	blendingAlphaBlending.removeListener(this, &ofApp::blendingAlphaBlendingChanged);
	blendingRampImage.removeListener(this, &ofApp::blendingRampImageChanged);

	blendingAdd = false;
	blendingSubtract = false;
	blendingAlphaBlending = false;
	blendingRampImage = false;

	blendingAdd.addListener(this, &ofApp::blendingAddChanged);
	blendingSubtract.addListener(this, &ofApp::blendingSubtractChanged);
	blendingAlphaBlending.addListener(this, &ofApp::blendingAlphaBlendingChanged);
	blendingRampImage.addListener(this, &ofApp::blendingRampImageChanged);
}

void ofApp::blendingAddChanged(bool& show)
{
	resetBlendings();
	blendingAdd = true;
	updateParameters();
}

void ofApp::blendingSubtractChanged(bool& show)
{
	resetBlendings();
	blendingSubtract = true;
	updateParameters();
}

void ofApp::blendingAlphaBlendingChanged(bool& show)
{
	resetBlendings();
	blendingAlphaBlending = true;
	updateParameters();
}

void ofApp::blendingRampImageChanged(bool& show)
{
	resetBlendings();
	blendingRampImage = true;
	updateParameters();
}

void ofApp::blendingRampStartChanged(int& value)
{
	updateParameters();
}

void ofApp::blendingRampEndChanged(int& value)
{
	updateParameters();
}

void ofApp::updateParameters()
{
    if (typeBlending)
        documentList.set_processing_type(kBlending);
    else if (typeCutting)
        documentList.set_processing_type(kCutting);
    
	if (blendingAdd) {
		blendingParams.type = kArithmeticAdd;
	} else if (blendingSubtract) {
		blendingParams.type = kArithmeticSubtract;
	} else if (blendingAlphaBlending) {
		blendingParams.type = kArithmeticAlphaBlend;
		blendingParams.alpha = blendingAlpha;
	} else if (blendingRampImage) {
		blendingParams.type = kArithmeticRampImage;
		blendingParams.rampStart = blendingRampStart;
		blendingParams.rampEnd = blendingRampEnd;
	}

	documentList.setBlendingParams(blendingParams);
	
	documentList.updateImage(UpdateImageType::kUpdateAll);
}
