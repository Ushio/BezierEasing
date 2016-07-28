#include "ofApp.h"

#include "BezierEasing.hpp"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    
    ofSetColor(255);
    
    _camera.begin();
    
    // グリッド
    ofPushMatrix();
    ofRotateY(90.0f);
    ofSetColor(255);
    ofDrawGridPlane(100.0f, 10, true);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofScale(100.0f, 100.0f, 100.0f);
    
    // http://cubic-bezier.com/#.79,-0.22,.22,.82
    BezierEasing e(0.79f, -0.22, 0.22, 0.82, 20 /* split */);
    for(auto p : e._pivots) {
        ofDrawCircle(p.first, p.second, 0.005f);
    }
    
    ofPolyline line;
    
    for(int i = 0 ; i < 100 ; ++i) {
        double x = ofMap(i, 0, 99, 0, 1);
        double y = e.evaluate(x);
        
        line.addVertex(x, y);
    }
    line.draw();
    
    double x = fmod(ofGetElapsedTimef() * 0.5f, 1.0f);
    double y = e.evaluate(x);
    ofSetColor(255, 0, 0);
    ofDrawSphere(x, y, 0.0f, 0.05f);
    
    ofPopMatrix();

    _camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
