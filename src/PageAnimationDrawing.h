#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"
#include "PageAnimation.h"

class PageAnimationDrawing : public PageAnimation
{
	
public:
	
	PageAnimationDrawing();
	
	void update();
	void draw();
	
private:
	
	Tween _tween;
	
	float _texCoords[8];
};