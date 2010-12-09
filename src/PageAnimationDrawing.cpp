#include "PageAnimationDrawing.h"

/* Constructor
 ___________________________________________________________ */

PageAnimationDrawing::PageAnimationDrawing()
{	
	cout << "Drawing made" << endl;
	
	int tempW = 200;
	int tempH = 280;
	
	_drawing = false;
	_tex.allocate(tempW, tempH, GL_RGB);
	
	resetBackground();
	
	_texCoords[0] = 0;
	_texCoords[1] = 0;
	
	_texCoords[2] = tempW;
	_texCoords[3] = 0;
	
	_texCoords[4] = tempW;
	_texCoords[5] = tempH; 
	
	_texCoords[6] = 0;
	_texCoords[7] = tempH;
}

/* Reset background of texture
 ___________________________________________________________ */

void PageAnimationDrawing::resetBackground()
{
	_tex.begin();
	ofFill();
	ofSetColor(240, 240, 240);
	ofRect(0, 0, _tex.getWidth(), _tex.getHeight());
	_tex.end();
}

/* Update
 ___________________________________________________________ */

void PageAnimationDrawing::update()
{	
	_tween.update();
	
	if(_drawingModel.isPlaying())
	{
		Dot * d = _drawingModel.getDot();
		
		if(d != NULL)
		{			
			if(!_drawing)
			{
				_curPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
				_lastPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
				
				_drawing = true;
			}
			
			_lastPos.set(_curPos);
			_curPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
		}
		
		if (_drawingModel.isMouseUp()) 
		{
			_drawing = false;
		}
	}
	
	if(_drawing && !_drawingModel.isFinished())
	{
		drawSinceLast();
	}
	
	if(_drawingModel.isFinished())
	{
		if(!_tween.isPlaying())
		{
			_tween.play();
		}
		
		if(_tween.finished())
		{
			_tween.stop();
			_finished = true;
		}
	}
}

/* Draw
 ___________________________________________________________ */

void PageAnimationDrawing::draw()
{	
	ofFill();
	ofSetColor(255, 255, 255);
	
	_tex.bind();
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad2D(_pageModel->pts[0].x, _pageModel->pts[0].y, _pageModel->pts[1].x, _pageModel->pts[1].y, _pageModel->pts[2].x, _pageModel->pts[2].y, _pageModel->pts[3].x, _pageModel->pts[3].y);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	_tex.unbind();
}

/* Draw line from last pos to cur pos
 ___________________________________________________________ */

void PageAnimationDrawing::drawSinceLast()
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
}

/* Draw a single dot
 ___________________________________________________________ */

void PageAnimationDrawing::drawPoint(float x, float y)
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


/* Show
 ___________________________________________________________ */

void PageAnimationDrawing::show()
{	
	_finished = false;
	
	resetBackground();
	
	_drawingModel.play();
	
	Dot * d = _drawingModel.getDotAtIndex(0);
	
	_curPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
	_lastPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
	
	_drawing = true;
	
	_tween.setup(100, 0, 100, Easing::LinearEaseIn);
}


