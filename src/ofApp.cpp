#include "ofApp.h"
list <ofTouchEventArgs> touches;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(51);
    ip = getIP();
    port = 8000;
    addres = "/touch/points";
    sender.setup(ip, port);
    ofSetFrameRate(30);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofHideCursor();
    ofxMultitouch::EnableTouch();
    // タッチイベントリスナーを追加
    ofAddListener(ofxMultitouch::touchDown, this, &ofApp::touchDown);
    ofAddListener(ofxMultitouch::touchMoved, this, &ofApp::touchMove);
    ofAddListener(ofxMultitouch::touchUp, this, &ofApp::touchUp);
}

//--------------------------------------------------------------
void ofApp::update(){
    list<ofTouchEventArgs> ::iterator it;
    if(touches.size() > 0){
        ofxOscMessage m;
        m.setAddress(addres);
        for (it = touches.begin(); it != touches.end(); ++it) {
            //タッチポイントを表示
            ofDrawCircle((*it).x, (*it).y, 50);
            m.addIntArg((*it).x);
            m.addIntArg((*it).y);
        }
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("IP: " + ip  + "  PORT: " + ofToString(port) + "  ADDRES:"+
    addres, 5, ofGetHeight()-10);
}

//--------------------------------------------------------------
void ofApp::oscSendPoint(int x, int y){
    
}

//--------------------------------------------------------------
string ofApp::getIP(){
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "en0", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    string ipAddress = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    //[*] check good ipAddress
    int pos = ipAddress.find_last_of(".");
    string last = ipAddress.substr(pos+1);
    if ((pos==string::npos )|| (last == "0")) ipAddress = "";
    return ipAddress;
}
//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch) {
    //タッチが検出されたら、ポイントを追加する
    touches.push_back(touch);
}
//--------------------------------------------------------------
void ofApp::touchMove(ofTouchEventArgs & touch) {
    //タッチポイントの移動を検出
    std::list <ofTouchEventArgs> ::iterator it;
    for (it = touches.begin(); it != touches.end(); ++it) {
        if (it->id == touch.id) {
            *it = touch;
        }
    }
}
//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch) {
    //タッチポイントが離れたときに、ポイントを削除する
    ofTouchEventArgs touchToRemove;
    std::list <ofTouchEventArgs> ::iterator it;
    for (it = touches.begin(); it != touches.end(); ++it) {
        if (it->id == touch.id) {
            touchToRemove = *it;
        }
    }
    touches.remove(touchToRemove);
}
