#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"

class PageAnimation
{
	
public:
	
	PageAnimation();
	
	void setAndPlay(string img, int duration, int delay);
	
	void update();
	void draw();
	
	bool finished;
	int modelid;
	
private:
	
	void reset();
	
	Tween _tween;
	ofImage _img;
	float _texCoords[8];
};