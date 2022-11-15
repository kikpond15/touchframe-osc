#pragma once

#include "ofMain.h"
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "ofxMultitouch.h"
#include "ofxOsc.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void touchDown(ofTouchEventArgs& touch);
    void touchMove(ofTouchEventArgs& touch);
    void touchUp(ofTouchEventArgs& touch);
    
    void oscSendPoint(int x, int y);
    string getIP();
    
    ofxOscSender sender;
    string ip, addres;
    int port;
};
