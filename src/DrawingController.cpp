#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
	allocateTextures();
	
	_drawing = false;
	
	_firstPress = true;
	
	_saveImg.loadImage("clicktosave.png");
}

/* Texture methods
 ___________________________________________________________ */

void DrawingController::allocateTextures()
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	cout << "Reallocated texture to: " << r.width << " x " << r.height << endl;
	cout << "Drawing Texture at: " << r.x << " , " << r.y << endl;
		
	_tex.allocate(r.width, r.height, GL_RGB);
	
	resetTexture();
}

void DrawingController::resetTexture()
{
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
	
	drawSaveImage();
	
	drawMouse();
}

/* Draw mouse
 ___________________________________________________________ */

void DrawingController::drawMouse()
{
	ofSetColor(0, 0, 0);
	ofFill();
	ofCircle(_mousePos.x, _mousePos.y, 5);
	ofNoFill();
	ofCircle(_mousePos.x, _mousePos.y, 5);
}

/* Draw save image
 ___________________________________________________________ */

void DrawingController::drawSaveImage()
{
	App * app = App::getInstance();
	
	int s = app->getModelsSize();
	
	if(s > 0)
	{
		Page * lastModel = app->getModelByIndex(s - 1);
		
		float saveCoords[8] = {0, 0, _saveImg.width, 0, _saveImg.width, _saveImg.height, 0, _saveImg.height};
		
		_saveImg.getTextureReference().bind();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, &saveCoords[0]);
		ofQuad2D(lastModel->pts[0].x, lastModel->pts[0].y, lastModel->pts[1].x, lastModel->pts[1].y, lastModel->pts[2].x, lastModel->pts[2].y, lastModel->pts[3].x, lastModel->pts[3].y);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		_saveImg.getTextureReference().unbind();
	}
}

/* Draw points from last pos to cur pos
 ___________________________________________________________ */

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

/* Draw a single point
 ___________________________________________________________ */

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

/* Save drawing
 ___________________________________________________________ */

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
}


/* Events
 ___________________________________________________________ */

void DrawingController::mouseMoved(int x, int y)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	float normX = (float) x / (float) ofGetWidth();
	float normY = (float) y / (float) ofGetHeight();
	
	_mousePos.x = r.x + (normX * r.width);
	_mousePos.y = r.y + (normY * r.height);
}

void DrawingController::mouseDragged(int x, int y, int button)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_lastPos.set(_curPos);
	
	_curPos.set(x - r.x, y - r.y);
}

void DrawingController::mousePressed(int x, int y, int button)
{
	if (_firstPress) 
	{
		_d.record();
		_firstPress = false;
	}
	
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
		if(ENABLE_SAVE)
		{
			saveDrawing();
		}
		
		_finished = true;
		
		reset();
	}
}

void DrawingController::reset()
{
	resetTexture();
	
	_d.reset();
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
