#include "testApp.h"

/* Setup
 _________________________________________________________________ */

void testApp::setup()
{
	ofSetWindowTitle("Dear...");

	ofSetFrameRate(60);
	
	ofBackground(0, 0, 0);
}

/* Update
 _________________________________________________________________ */

void testApp::update()
{
	plotter.update();
	pages.update();
}

/* Draw
 _________________________________________________________________ */

void testApp::draw()
{
	plotter.draw();
	
	if(!plotter.getRecordMode())
	{
		pages.draw();
	}
}

/* Key Events
 _________________________________________________________________ */

void testApp::keyPressed  (int key)
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
}

void testApp::mousePressed(int x, int y, int button)
{
	plotter.mousePressed(x, y, button);
}

void testApp::keyReleased  (int key) {}
void testApp::mouseMoved(int x, int y ) {}
void testApp::mouseReleased(int x, int y, int button) {}
void testApp::windowResized(int w, int h) {}