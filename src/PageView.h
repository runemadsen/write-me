#pragma once

#include "ofMain.h"
#include "View.h"
#include "App.h"
#include "ofQuad.h"

class PageView : public View
{

public:
	
	PageView();
	
	void update();
	void draw();
	
private:
	
	float _texCoords[8];
};