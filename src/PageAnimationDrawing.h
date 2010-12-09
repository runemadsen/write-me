#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"
#include "PageAnimation.h"
#include "ofxFBOTexture.h"

class PageAnimationDrawing : public PageAnimation
{
	
public:
	
	PageAnimationDrawing();
	
	void update();
	void draw();
	void show();
	
private:
	
	void drawPoint(float x, float y);
	void drawSinceLast();
	
	Tween _tween;
	
	ofxFBOTexture _tex;
	float _texCoords[8];
	
	ofxVec2f _lastPos;
	ofxVec2f _curPos;
	bool _drawing;
};