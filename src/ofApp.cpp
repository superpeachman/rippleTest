#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.loadImage("demo.jpg");
    w = image.width;
    h = image.height;
    pixels = w * h;
    updatedImage.allocate(w, h, OF_IMAGE_COLOR);//allocate 
    
    light.normalize();
    
    tempV.resize(pixels);
    odata.resize(pixels);
    ndata.resize(pixels);
    
    for (int i=0; i<pixels; i++) {
        tempV[i] = 0.0;
        odata[i] = 0.0;
        ndata[i] = 0.0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    printf("Framerate: %f \n", ofGetFrameRate());
    if (ofRandom(1) < 0.3) ripple();// Ripple happen automatically.
    
    sim();//Spread old ripples.
    
    for (int i=0; i<pixels; i++) {//Make each first ripple
        int x = i % w;
        int y = i / w;
        
        ofVec3f n = ofVec3f(getVal(x - eps, y) - getVal(x + eps, y), getVal(x, y - eps) - getVal(x, y + eps), eps * 2.0);//Check pixels around
        n.normalize();
        float spec = (1 - (light.x + n.x)) + (1 - (light.y + n.y));
        spec /= 2;
        
        if (spec > z)
            spec = (spec - z) / (1 - z);
        else
            spec = 0;
        
        spec *= 255.0;
        
        ofColor c = image.getColor(x + n.x * 60, y + n.y * 60);//Get "edge" of ripple
        c += spec;//Make "edge" brighter
        updatedImage.setColor(x, y, c);
    }
    updatedImage.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    updatedImage.draw(0, 0);
}

//--------------------------------------------------------------
float ofApp::getVal(int x, int y){
    if (x < 1 || y < 1 || x >= w - 1 || y >= h - 1){return 0;}
    float a = odata[x+y*w];
    return a;
}

//--------------------------------------------------------------
void ofApp::sim(){
    //Store current situation then update.
    for (int i=0; i<pixels; i++) {
        tempV[i] = odata[i];
    }
    for (int i=0; i<pixels; i++) {
        odata[i] = ndata[i];
    }
    for (int i=0; i<pixels; i++) {
        ndata[i] = tempV[i];
    }
    
    //Spread
    for (int i=0; i<pixels; i++) {
        int x = i % w;
        int y = i / w;
        if (x > 1 || y > 1 || x <= w - 1 || y <= h - 1){
            float val = (odata[(x-1)+y*w] + odata[(x+1)+y*w] + odata[x+(y-1)*w] + odata[x+(y+1)*w]) / 2;
            val = val - ndata[x+y*w];
            val *= 0.96875;
            ndata[x+y*w] = val;
        }
    }
}
//--------------------------------------------------------------
void ofApp::ripple(){
    //Randomly make ripple
    int rx = (int)ofRandom(w - 10) + 5;
    int ry = (int)ofRandom(h - 10) + 5;
    for (int x = -5; x < 5; x++){
        for (int y = -5; y < 5; y++){
            int targetPix = (rx + x) + (w * (ry + y));
            odata[targetPix] = 100;
        }
    }
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
    //Make ripple
    for (int x = -10; x < 10; x++) {
        for (int y = -10; y < 10; y++) {
            int targetPix = (mouseX + x) + (w * (mouseY + y));
            odata[targetPix] = 0.1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
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
