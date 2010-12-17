#include "DrawingController.h"

/* Constructor
 ___________________________________________________________ */

DrawingController::DrawingController()
{		
	allocateTextures();
	
	_drawing = false;
	
	_firstPress = true;
	
	_saveImg.loadImage("clicktosave.png");
	
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
	_mask.allocate(r.width, r.height, GL_RGBA);
	
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
	
	_mask.begin();
	ofFill();
	ofSetColor(0, 0, 0);
	ofRect(0, 0, _mask.getWidth(), _mask.getHeight());
	
	ofSetColor(255, 0, 0);
	for (int i = 0; i < app->getPageModelsSize(); i++) 
	{
		Page * model = app->getModelByIndex(i);
		
		ofBeginShape();
		
		for (int j = 0; j < model->pts.size(); j++) 
		{
			ofVertex(model->pts[j].x - r.x, model->pts[j].y - r.y);
		}
		
		ofEndShape(true);
	}
	
	_mask.end();
	
	unsigned char * pix = (unsigned char *) _mask.getPixels();
	
	for(int i = 0; i < _mask.getWidth() * _mask.getHeight(); i++)
	{
		if(pix[i * 4] == 255)
		{
			pix[i * 4 + 3] = 0; 	// alpha
		}
		else 
		{
			pix[i * 4 + 3] = 255; 	// alpha
		}

		pix[i * 4] = 0;	// r
		pix[i * 4 + 1] = 0;	// g
		pix[i * 4 + 2] = 0;   // b
	}
	
	_finalMask.allocate(_mask.getWidth(), _mask.getHeight(), GL_RGBA);
	_finalMask.loadData(pix, _mask.getWidth(), _mask.getHeight(), GL_RGBA);
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
	
	//drawSaveImage();
	
	drawMouse();
}

/* Draw texture
 ___________________________________________________________ */

void DrawingController::drawTexture()
{
	ofSetColor(255, 255, 255);
	
	ofRectangle r = App::getInstance()->getModelBounds();
	
	ofEnableAlphaBlending();
	
	ofSetColor(255, 255, 255, _fader.num);
	_tex.draw(r.x, r.y, _tex.getWidth(), _tex.getHeight());
	
	ofSetColor(0, 0, 0, 255);
	_finalMask.draw(r.x, r.y, _mask.getWidth(), _mask.getHeight());
	
	ofDisableAlphaBlending();
}

/* Draw save image
 ___________________________________________________________ */

void DrawingController::drawSaveImage()
{
	App * app = App::getInstance();
	
	int s = app->getPageModelsSize();
	
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
		_d.record();
		
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
	_d.stopRecording();
	_d.reset();
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
