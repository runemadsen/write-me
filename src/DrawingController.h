#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"

class DrawingController
{
	
public:
	
	DrawingController();
	
	void update();
	void draw();
	
	void show();
	
	bool finished;
	
	void mouseMoved(int x, int y);
	
private:
	
	long _lastDraw;
};