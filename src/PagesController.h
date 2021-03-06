#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "App.h"
#include "PageAnimation.h"
#include "Animation.h"

class PagesController : public Animation
{
	
public:
	
	PagesController();
	
	void update();
	void draw();
	void show();
	void hide();

	void createNewViews();
	
	void setDrawing(int pageID, int drawingIndex);
	
private:
	
	Drawing * getRandomDrawingModel();
	
	vector <PageAnimation *> _views;
	
	int _blank_page;
	
	ofxXmlSettings _xml;
};