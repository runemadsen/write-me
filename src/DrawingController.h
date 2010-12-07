#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Animation.h"
#include "ofxFBOTexture.h"

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
	
private:
	
	long _lastDraw;
	ofxFBOTexture _tex;
	
};