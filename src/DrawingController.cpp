#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{	
	finished = false;
	
	_lastDraw = ofGetElapsedTimeMillis();
}

/* Update
 ___________________________________________________________ */

void DrawingController::update()
{	
	cout << "Calc: " << ofGetElapsedTimeMillis() - _lastDraw << endl;
	
	if(ofGetElapsedTimeMillis() - _lastDraw > 3000)
	{
		cout << "Setting finished to true \n";
		finished = true;
	}
}

/* Draw
 ___________________________________________________________ */

void DrawingController::draw()
{	
	/*App * app = App::getInstance();
	
	for (int i = 0; i < app->models.size(); i++) 
	{
		
	}*/
	
	ofSetColor(255, 255, 255);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}

/* mouse Moved
 ___________________________________________________________ */

void DrawingController::mouseMoved(int x, int y)
{
	_lastDraw = ofGetElapsedTimeMillis();
}

void DrawingController::show()
{
	finished = false;
	
	_lastDraw = ofGetElapsedTimeMillis();
}
