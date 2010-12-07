#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
	_lastDraw = ofGetElapsedTimeMillis();
	_tex.allocate(DRAWING_TEXTURE_SIZE, DRAWING_TEXTURE_SIZE, GL_RGB);
}

/* Update
 ___________________________________________________________ */

void DrawingController::update()
{	
	ofRectangle r = App::getInstance()->getModelBounds();
	
	if(r.width != _tex.getWidth() || r.height != _tex.getHeight())
	{
		cout << "Reallocated texture to: " << r.width << " x " << r.height << endl;
		cout << "Drawing at: " << r.x << " , " << r.y << endl;
		
		_tex.allocate(r.width, r.height, GL_RGB);
	}
	
	if(ofGetElapsedTimeMillis() - _lastDraw > 3000)
	{
		_finished = true;
	}
}

/* Draw
 ___________________________________________________________ */

void DrawingController::draw()
{	
	ofSetColor(255, 255, 255);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_tex.draw(r.x, r.y, _tex.getWidth(), _tex.getHeight());
}

/* mouse Moved
 ___________________________________________________________ */

void DrawingController::mouseMoved(int x, int y)
{
	_lastDraw = ofGetElapsedTimeMillis();
}

void DrawingController::mouseDragged(int x, int y, int button)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_lastDraw = ofGetElapsedTimeMillis();

	_tex.begin();
	
	ofSetColor(255, 0, 0);
	ofCircle(x - r.x, _tex.getHeight() - (y - r.y), 10);
	
	_tex.end();
}

void DrawingController::show()
{
	_finished = false;
	
	_lastDraw = ofGetElapsedTimeMillis();
}

void DrawingController::hide()
{
	_finished = false;
}
