#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFullscreen(true);
  cam.setDeviceID(1);
  cam.initGrabber(ofGetWidth(), ofGetHeight());
  gui.setup();
  gui.add(pyrScale.setup("pyrScale", .5, 0, 1));
  gui.add(levels.setup("levels", 4, 1, 8));
  gui.add(winsize.setup("levels", 8, 4, 64));
  gui.add(iterations.setup("iterations", 2, 1, 8));
  gui.add(polyN.setup("polyN", 7, 5, 10));
  gui.add(polySigma.setup("polySigma", 1.5, 1.1, 2));
  gui.add(
      OPTFLOW_FARNEBACK_GAUSSIAN.setup("OPTFLOW_FARNEBACK_GAUSSIAN", false));

  gui.add(useFarneback.setup("useFarneback", false));
  gui.add(winSize.setup("windSize", 32, 4, 64));
  gui.add(maxLevel.setup("maxLevel", 3, 0, 8));
  gui.add(levels.setup("maxFreatures", 200, 1, 1000));
  gui.add(qualityLevel.setup("levels", 0.01, 0.001, 0.02));
  gui.add(minDistance.setup("minDistance", 4, 1, 16));
  curFlow = &farneback;
}

//--------------------------------------------------------------
void ofApp::update() {
  cam.update();
  if (cam.isFrameNew()) {
    curFlow = &farneback;
    farneback.setPyramidScale(pyrScale);
    farneback.setNumLevels(levels);
    farneback.setWindowSize(winsize);
    farneback.setNumIterations(iterations);
    farneback.setPolyN(polyN);
    farneback.setPolySigma(polySigma);
    farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
  } else {
    curFlow = &pyrLK;
    pyrLK.setMaxFeatures(maxFeatures);
    pyrLK.setQualityLevel(qualityLevel);
    pyrLK.setMinDistance(minDistance);
    pyrLK.setWindowSize(winSize);
    pyrLK.setMaxLevel(maxLevel);
  }
  curFlow->calcOpticalFlow(cam);
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0);
  ofSetColor(255);
  cam.draw(0, 0, ofGetWidth(), ofGetHeight());
  curFlow->draw(0, 0, ofGetWidth(), ofGetHeight());
  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
