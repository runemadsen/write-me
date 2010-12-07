#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Tween.h"
#include "ofQuad.h"
#include "PageAnimation.h"

class PageAnimationBlank : public PageAnimation
{
	
public:
	
	PageAnimationBlank();
	
	void update();
	void draw();
	
private:
	
	Tween _tween;
};