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
	void hide();
	
private:
	
	void setupTexture();
	void drawPoint(float x, float y);
	void drawSinceLast();
	
	void resetBackground();
	
	Tween _tweenUp;
	Tween _tweenDown;
	
	ofxFBOTexture _tex;
	float _texCoords[8];
	
	ofxVec2f _lastPos;
	ofxVec2f _curPos;
	bool _drawing;
};