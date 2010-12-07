#include "testApp.h"

/* Setup
 _________________________________________________________________ */

void testApp::setup()
{
	curAnimation = 0;
	
	ofSetWindowTitle("Dear...");

	ofSetFrameRate(60);
	
	ofBackground(0, 0, 0);
	
	animations.push_back( new PagesController() );
	animations.push_back( new DrawingController() );
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
		int newAnimation = curAnimation == 0 ? 1 : 0;
		
		changeAnimation(newAnimation);
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

/* Change Animation
 _________________________________________________________________ */

void testApp::changeAnimation(int i)
{
	animations[curAnimation]->hide();
	
	curAnimation = i;
	
	animations[curAnimation]->show();
}

/* Key Events
 _________________________________________________________________ */

void testApp::keyPressed(int key)
{
	plotter.keyPressed(key);
	
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}

void testApp::mouseDragged(int x, int y, int button)
{
	plotter.mouseDragged(x, y, button);
	
	animations[curAnimation]->mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button)
{
	plotter.mousePressed(x, y, button);
}

void testApp::keyReleased  (int key) {}

void testApp::mouseMoved(int x, int y ) 
{
	if(!plotter.getRecordMode())
	{
		if(curAnimation == 0)
		{
			changeAnimation(1);
			cout << "Switching to drawing mode \n";
			animations[curAnimation]->show();
		}
		
		animations[curAnimation]->mouseMoved(x, y);
	}
}

void testApp::mouseReleased(int x, int y, int button) {}
void testApp::windowResized(int w, int h) {}