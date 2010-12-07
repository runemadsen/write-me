#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "App.h"
#include "PageAnimation.h"
#include "ofxDirList.h"

class PagesController
{
	
public:
	
	PagesController();
	
	void update();
	void draw();
	
	void changePages();

	void assignModelsToViews();
	
private:
	
	vector <PageAnimation *> _views;
};