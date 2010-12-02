#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "App.h"
#include "PageView.h"

class PagesController
{
	
public:
	
	PagesController();
	
	void update();
	void draw();

	void assignModelsToViews();
	
private:
	
	vector <PageView *> _views;
	
	ofImage _img;
	
	ofVideoPlayer testVid;
};