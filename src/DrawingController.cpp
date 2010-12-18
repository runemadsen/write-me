#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
	allocateTextures();
	
	_drawing = false;
	
	_firstPress = true;
	
	_fader.setup(50, 100, 255, Easing::QuartEaseIn, 0, 2);
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
	App * app = App::getInstance();
	ofRectangle r = App::getInstance()->getModelBounds();
	
	_tex.begin();
	ofFill();
	ofSetColor(255, 255, 255);
	ofRect(0, 0, _tex.getWidth(), _tex.getHeight());
	_tex.end();
	
	_texCoords[0] = 0;
	_texCoords[1] = 0;
	
	_texCoords[2] = _tex.getWidth();
	_texCoords[3] = 0;
	
	_texCoords[4] = _tex.getWidth();
	_texCoords[5] = _tex.getHeight(); 
	
	_texCoords[6] = 0;
	_texCoords[7] = _tex.getHeight();
}

/* Update
 ___________________________________________________________ */

void DrawingController::update()
{	
	_fader.update();
	
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
	ofSetColor(0, 0, 0);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	drawTexture();
	
	drawMouse();
}

/* Draw texture
 ___________________________________________________________ */

void DrawingController::drawTexture()
{
	ofSetColor(255, 255, 255);
	
	ofRectangle r = App::getInstance()->getModelBounds();
	Page * model = App::getInstance()->getPageModelByIndex(0);
	
	_tex.bind();
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad2D(model->pts[0].x, model->pts[0].y, model->pts[1].x, model->pts[1].y, model->pts[2].x, model->pts[2].y, model->pts[3].x, model->pts[3].y);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	_tex.unbind();
	
	//ofEnableAlphaBlending();
//	
//	ofSetColor(255, 255, 255, _fader.num);
//	_tex.draw(r.x, r.y, _tex.getWidth(), _tex.getHeight());
//	
//	ofDisableAlphaBlending();
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
			
		_recorder.addNormDot(_curPos.x / (float) _tex.getWidth(), _curPos.y / (float) _tex.getHeight());
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
	ofTranslate(x, y);
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
	ofRectangle r = App::getInstance()->getModelBounds();
	ofPoint mousePos = getMousePosInTexture(x, y);
		
	_mousePos.x = r.x + mousePos.x;
	_mousePos.y = r.y + mousePos.y;
}

void DrawingController::mouseDragged(int x, int y, int button)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	ofPoint mousePos = getMousePosInTexture(x, y);
	
	_mousePos.x = r.x + mousePos.x;
	_mousePos.y = r.y + mousePos.y;
	
	_lastPos.set(_curPos);
	
	_curPos.set(mousePos.x, mousePos.y);
}

void DrawingController::mousePressed(int x, int y, int button)
{
	if (_firstPress) 
	{
		_recorder.record();
		
		_firstPress = false;
	}
	
	ofRectangle r = App::getInstance()->getModelBounds();
	ofPoint mousePos = getMousePosInTexture(x, y);
	
	_curPos.set(mousePos.x, mousePos.y);
	_lastPos.set(mousePos.x, mousePos.y);
	
	_drawing = true;
}

void DrawingController::mouseReleased(int x, int y, int button)
{
	_drawing = false;
	
	_recorder.addMouseUp();
}

void DrawingController::keyPressed(int key)
{
	if(key == 'c')
	{
		_recorder.stopRecording();
		
		reset();
		
		_finished = true;
	}
}


/* Tools
 ___________________________________________________________ */

ofPoint DrawingController::getMousePosInTexture(int x, int y)
{
	ofRectangle r = App::getInstance()->getModelBounds();
	
	ofPoint pos;
	
	float normX = (float) x / (float) ofGetWidth();
	float normY = (float) y / (float) ofGetHeight();
	
	pos.x = normX * r.width;
	pos.y = normY * r.height;
	
	return pos;
}


void DrawingController::reset()
{
	resetTexture();
	
	_firstPress = true;
	_fader.stop();
}

/* Show / Hide
 ___________________________________________________________ */

void DrawingController::show()
{
	_finished = false;
	_fader.play();
}

void DrawingController::hide()
{
	_finished = false;
	
	reset();
}
