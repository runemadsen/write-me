#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "App.h"
#include "PageAnimation.h"
#include "ofxDirList.h"
#include "Animation.h"
#include "PageAnimationImage.h"
#include "PageAnimationBlank.h"

class PagesController : public Animation
{
	
public:
	
	PagesController();
	
	void update();
	void draw();
	
	void changePages();

	void assignModelsToViews();
	
private:
	
	vector <PageAnimation *> _views;
	
	int _blank_page;
};