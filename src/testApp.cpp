#include "testApp.h"

/* Setup
 _________________________________________________________________ */

void testApp::setup()
{
	curAnimation = 0;
	
	App::getInstance()->loadDrawingModels();
	
	ofEnableSmoothing();
	
	ofSetWindowTitle("Dear...");

	ofSetFrameRate(60);
	
	ofBackground(0, 0, 0);
	
	animations.push_back( new PagesController() );
	animations.push_back( new DrawingController() );
	
	ofAddListener(tablet.penDragged, this, &testApp::onPenDragged);
	ofAddListener(tablet.penUp, this, &testApp::onPenUp);
	ofAddListener(tablet.penDown, this, &testApp::onPenDown);
	ofAddListener(tablet.penEnter, this, &testApp::onPenEnter);
	ofAddListener(tablet.penLeave, this, &testApp::onPenLeave);
	ofAddListener(tablet.penMove, this, &testApp::onPenMove);
	
	ofHideCursor();
}

/* Update
 _________________________________________________________________ */

void testApp::update()
{
	plotter.update();
	
	if(!plotter.getRecordMode())
	{
		animations[curAnimation]->update();
	}
	
	if (animations[curAnimation]->getFinished()) 
	{
		curAnimation = curAnimation == 0 ? 1 : 0;
		
		animations[curAnimation]->show();
	}
}

/* Draw
 _________________________________________________________________ */

void testApp::draw()
{
	plotter.draw();
	
	if(!plotter.getRecordMode())
	{
		animations[curAnimation]->draw();
	}
}

/* Key Events
 _________________________________________________________________ */

void testApp::keyPressed(int key)
{
	plotter.keyPressed(key);
	
	if(plotter.getRecordMode())
	{
		ofShowCursor();
	}
	else 
	{
		ofHideCursor();
	}
	
	animations[curAnimation]->keyPressed(key);
	
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}

/* Mouse Events
 _________________________________________________________________ */

void testApp::mouseDragged(int x, int y, int button)
{
	plotter.mouseDragged(x, y, button);
	
	animations[curAnimation]->mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button)
{
	plotter.mousePressed(x, y, button);
	
	animations[curAnimation]->mousePressed(x, y, button);
}

void testApp::keyReleased  (int key) {}

void testApp::mouseMoved(int x, int y ) 
{
	if(!plotter.getRecordMode())
	{
		if(curAnimation == 0)
		{
			cout << "Switching to Drawing Controller" << endl;
			
			animations[curAnimation]->hide();
		}
		
		animations[curAnimation]->mouseMoved(x, y);
	}
}

void testApp::mouseReleased(int x, int y, int button) 
{
	animations[curAnimation]->mouseReleased(x, y, button);
}

void testApp::windowResized(int w, int h) {}

/* tableet Events
 _________________________________________________________________ */

void testApp::onPenDragged(ofxTabletArgs& e)
{	
}

void testApp::onPenUp(ofxTabletArgs& e)
{
}

void testApp::onPenDown(ofxTabletArgs& e)
{
}

void testApp::onPenEnter(ofxTabletArgs& e){
}

void testApp::onPenLeave(ofxTabletArgs& e){
}

void testApp::onPenMove(ofxTabletArgs& e){
}