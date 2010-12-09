#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
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
		
		// draw as many length on normalize * length
		for (int i = 1; i <= len; i++) 
		{
			float xPos = _lastPos.x + (vec.x * (float) i);
			float yPos = _lastPos.y + (vec.y * (float) i);
			
			drawPoint(xPos, yPos);
		}
		
		drawPoint(_curPos.x, _curPos.y);
			
		_d.addNormDot(_curPos.x / (float) _tex.getWidth(), _curPos.y / (float) _tex.getHeight());
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
	ofRotateZ(ranRot);
	
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
	
	// make sure we don't get mouseups after finished?
	_d.addMouseUp();
}

void DrawingController::keyPressed(int key)
{
	if(key == 'c')
	{
		saveDrawing();
	}
}

void DrawingController::saveDrawing()
{	
	_xml.loadFromBuffer("<root></root>");
	
	_xml.clear();
	
	_xml.addTag(DRAWING);
	_xml.pushTag(DRAWING, 0);
	
		_xml.addTag(POINTS);
		_xml.pushTag(POINTS, 0);

		for(int i = 0; i < _d.getSize(); i++)
		{
			_xml.addTag(POINT);
			_xml.addAttribute(POINT, X, ofToString(_d.getDotAtIndex(i)->x, 2), i);
			_xml.addAttribute(POINT, Y, ofToString(_d.getDotAtIndex(i)->y, 2), i);
			_xml.addAttribute(POINT, MS, ofToString(_d.getDotAtIndex(i)->ms, 0), i);
		}
		
		_xml.popTag();
	
		_xml.addTag(MOUSE_UPS);
		_xml.pushTag(MOUSE_UPS, 0);
	
		for(int i = 0; i < _d.getMouseUpsSize(); i++)
		{
			_xml.addTag(MOUSE_UP);
			_xml.addAttribute(MOUSE_UP, MS, ofToString(_d.getMouseUpAtIndex(i), 0), i);
		}
		
		_xml.popTag();
	
	string file = ofToString(ofGetYear());
	file += "-";
	file += ofToString(ofGetMonth());
	file += "-";
	file += ofToString(ofGetDay());
	file += "-";
	file += ofToString(ofGetHours());
	file += "-";
	file += ofToString(ofGetMinutes());
	file += "-";
	file += ofToString(ofGetSeconds());
	
	_xml.saveFile(DRAWING_FOLDER + file + ".xml");
	
	// make sure to load this file into a drawing
}

/* Show / Hide
 ___________________________________________________________ */

void DrawingController::show()
{
	_finished = false;
}

void DrawingController::hide()
{
	_finished = false;
}
