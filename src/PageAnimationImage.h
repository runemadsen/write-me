#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"
#include "PageAnimation.h"

class PageAnimationImage : public PageAnimation
{
	
public:
	
	PageAnimationImage();
	
	void setAndPlay(string img, int duration, int delay);
	
	void update();
	void draw();
	
private:
	
	void reset();
	
	Tween _tween;
	ofImage _img;
	float _texCoords[8];
};