#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"

class Page
{
	
public:
	
	void addDefaultPoints(int xPos, int yPos)
	{
		int margin = 15;
		
		ofxVec2f pt;
		
		// top left
		pt.x = xPos - margin;
		pt.y = yPos - margin;
		pts.push_back(pt);
		
		// top right
		pt.x = xPos + margin;
		pt.y = yPos - margin;
		pts.push_back(pt);
		
		// bottom right
		pt.x = xPos + margin;
		pt.y = yPos + margin;
		pts.push_back(pt);
		
		// bottom left
		pt.x = xPos - margin;
		pt.y = yPos + margin;
		pts.push_back(pt);
	}
	
	vector <ofxVec2f> pts;
	
	int id;
	
private:
	
};
