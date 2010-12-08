#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Animation.h"
#include "ofxFBOTexture.h"
#include "ofxVec2f.h"

class DrawingController : public Animation
{
	
public:
	
	DrawingController();
	
	void update();
	void draw();
	
	void show();
	void hide();
	
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	
	void drawSinceLast();
	
	void allocateTextures();
	
	void drawPoint(float x, float y);
	
private:
	
	long _lastDraw;
	ofxFBOTexture _tex;
	
	ofImage _paper;
	
	bool _drawing;
	
	ofxVec2f _lastPos;
	ofxVec2f _curPos;
};