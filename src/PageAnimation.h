#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"
#include "Animation.h"
#include "ofxFBOTexture.h"
#include "PlayHelper.h"

class PageAnimation : public Animation
{
	
public:
	
	PageAnimation();
	
	void update();
	void draw();
	void show();
	void hide();
	
	void setPageModel(Page * pageModel);
	void setDrawingModel(Drawing * drawingModel);
	
	Page * getPageModel() { return _pageModel; }
	Drawing * getDrawingModel() { return _drawingModel; }
	
	bool getFinished() { return _finished; }	
	
private:
	
	void setupTexture();
	void drawPoint(float x, float y);
	void drawSinceLast();
	
	void resetBackground();
	
	Tween _tweenDown;
	
	ofxFBOTexture _tex;
	float _texCoords[8];
	
	ofxVec2f _lastPos;
	ofxVec2f _curPos;
	bool _drawing;
	
	PlayHelper _player;
	
	bool _finished;
	
	Page * _pageModel;
	Drawing * _drawingModel;
};