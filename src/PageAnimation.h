#pragma once

#include "Animation.h"
#include "Drawing.h"

class PageAnimation : Animation
{
	
public:
	
	PageAnimation() 
	{
		_finished = false;
		
		_pageModel = NULL;
	}
	
	virtual void update() {}
	virtual void draw() {}
	virtual void show() { _finished = false; }
	virtual void hide() { _finished = true; }
	
	virtual void keyPressed(int key) {}
	virtual void mouseMoved(int x, int y) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
	
	void setPageModel(Page * pageModel) { _pageModel = pageModel; }
	void setDrawingModel(Drawing * drawingModel) { _drawingModel = drawingModel; }
	
	Page * getPageModel() { return _pageModel; }
	Drawing * getDrawingModel() { return _drawingModel; }
	
	bool getFinished() { return _finished; }
	
protected:
	
	bool _finished;
	
	Page * _pageModel;
	Drawing * _drawingModel;
	
private:
	
};
