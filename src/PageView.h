#pragma once

#include "ofMain.h"
#include "View.h"
#include "App.h"
#include "ofQuad.h"

class PageView : public View
{

public:
	
	PageView(ofImage * img);
	
	void update();
	void draw();
	
private:
	
	ofImage * _img;
	float _texCoords[8];
};