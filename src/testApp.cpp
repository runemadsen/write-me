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
	
	if(mode == ANIMATION_MODE)
	{
		pages.update();
	}
	else 
	{
		drawing.update();
		
		if(drawing.finished)
		{
			cout << "Switching to animation mode \n";
			mode = ANIMATION_MODE;
		}
	}
		
	
}

/* Draw
 _________________________________________________________________ */

void testApp::draw()
{
	plotter.draw();
	
	if(!plotter.getRecordMode())
	{
		if(mode == DRAWING_MODE)
		{
			drawing.draw();
		}
		else 
		{
			pages.draw();
		}
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

void testApp::mouseMoved(int x, int y ) 
{
	if(!plotter.getRecordMode())
	{
		cout << "Mouse Moved \n";
		
		if(mode == DRAWING_MODE)
		{
			cout << "Is in drawing mode \n";
			drawing.mouseMoved(x, y);
		}
		else 
		{
			cout << "Switching to drawing mode \n";
			mode = DRAWING_MODE;
			drawing.show();
		}
	}
}

void testApp::mouseReleased(int x, int y, int button) {}
void testApp::windowResized(int w, int h) {}