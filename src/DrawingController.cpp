#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
	//_lastDraw = ofGetElapsedTimeMillis();
	
	_paper.loadImage("paper.png");
	
	allocateTextures();
	
	_drawing = false;
}

void DrawingController::allocateTextures()
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	cout << "Reallocated texture to: " << r.width << " x " << r.height << endl;
	cout << "Drawing Texture at: " << r.x << " , " << r.y << endl;
		
	_tex.allocate(r.width, r.height, GL_RGB);
	
	_tex.begin();
	ofFill();
	ofSetColor(240, 240, 240);
	ofRect(0, 0, _tex.getWidth(), _tex.getHeight());
	_tex.end();
}

/* Update
 ___________________________________________________________ */

void DrawingController::update()
{	
	ofRectangle r = App::getInstance()->getModelBounds();
	
	if(r.width != _tex.getWidth() || r.height != _tex.getHeight())
	{
		allocateTextures();
	}
	
	drawSinceLast();
	
	/*if(ofGetElapsedTimeMillis() - _lastDraw > 3000)
	{
		_finished = true;
	}*/
}

/* Draw
 ___________________________________________________________ */

void DrawingController::draw()
{	
	ofFill();
	ofSetColor(255, 255, 255);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_tex.draw(r.x, r.y, _tex.getWidth(), _tex.getHeight());
}

void DrawingController::drawSinceLast()
{	
	if(_drawing)
	{
		float len = _lastPos.distance(_curPos);
		
		ofxVec2f vec = _curPos - _lastPos;
		vec.normalize();
		
		cout << "Length: " << len << endl;
		cout << "Norm: " << vec.x << " , " << vec.y << endl;
		
		// draw as many length on normalize * length
		for (int i = 1; i <= len; i++) 
		{
			float xPos = _lastPos.x + (vec.x * (float) i);
			float yPos = _lastPos.y + (vec.y * (float) i);
			
			drawPoint(xPos, yPos);
			
			if(i == 50)
				cout << "Drawing at: " << xPos << " , " << yPos << endl;
		}
		
		drawPoint(_curPos.x, _curPos.y);
	}	
}

void DrawingController::drawPoint(float x, float y)
{
	// draw last point also
	float ranWidth = ofRandom(2, 7);
	float ranHeight = ofRandom(1, 3);
	float ranAlpha = ofRandom(50, 100); 
	float ranRot = ofRandom(-30, 30);
	
	_tex.begin();
	
	ofPushMatrix();
	ofTranslate(x, _tex.getHeight() - y);
	//ofRotateZ(ranRot);
	
	ofEnableAlphaBlending();
	
	ofSetColor(0, 0, 0, ranAlpha);
	ofFill();
	ofEllipse(0, 0, ranWidth, ranHeight);
	ofNoFill();
	ofEllipse(0, 0, ranWidth, ranHeight);
	
	ofDisableAlphaBlending();
	ofPopMatrix();
	
	_tex.end();
}

/* Events
 ___________________________________________________________ */

void DrawingController::mouseMoved(int x, int y)
{
	//_lastDraw = ofGetElapsedTimeMillis();
}

void DrawingController::mouseDragged(int x, int y, int button)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_lastPos.set(_curPos);
	
	_curPos.set(x - r.x, y - r.y);
}

void DrawingController::mousePressed(int x, int y, int button)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_curPos.set(x - r.x, y - r.y);
	_lastPos.set(x - r.x, y - r.y);
	
	_drawing = true;
}

void DrawingController::mouseReleased(int x, int y, int button)
{
	_drawing = false;
}

void DrawingController::keyPressed(int key)
{
	if(key == 'c')
	{
		_finished = true;
	}
}

/* Show / Hide
 ___________________________________________________________ */

void DrawingController::show()
{
	_finished = false;
	
	//_lastDraw = ofGetElapsedTimeMillis();
}

void DrawingController::hide()
{
	_finished = false;
}
