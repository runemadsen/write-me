#include "PageAnimation.h"

/* Constructor
 ___________________________________________________________ */

PageAnimation::PageAnimation()
{	
	_finished = false;
	
	_pageModel = NULL;
	_drawingModel = NULL;
	
	_drawing = false;
		
	_tweenDown.setup(100, 0, 255, Easing::QuadEaseIn);
	
	setupTexture();
}

/* Setup texture
 ___________________________________________________________ */

void PageAnimation::setupTexture()
{
	int tempW = 200;
	int tempH = 280;
	
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

void PageAnimation::resetBackground()
{
	cout << "Resetting background" << endl;
	
	_tex.begin();
	ofFill();
	ofSetColor(255, 255, 255);
	ofRect(0, 0, _tex.getWidth(), _tex.getHeight());
	_tex.end();
}

/* Update
 ___________________________________________________________ */

void PageAnimation::update()
{	
	_tweenDown.update();
	
	if(_player.isPlaying())
	{
		Dot * d = _player.isDot();
		
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
		
		if (_player.isMouseUp()) 
		{
			cout << "Mouse up" << endl;
			
			_drawing = false;
		}
	}
	
	if(_drawing && !_player.isFinished())
	{
		drawSinceLast();
	}
	
	if(_player.isFinished())
	{
		if(!_tweenDown.isPlaying())
		{
			_tweenDown.play();
		}
		
		if(_tweenDown.finished())
		{
			_tweenDown.stop();
			_finished = true;
			
			cout << "Setting finished \n ";
		}
	}
}

/* Draw
 ___________________________________________________________ */

void PageAnimation::draw()
{	
	ofFill();
	ofSetColor(255, 255, 255);
	
	_tex.bind();
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad2D(_pageModel->pts[0].x, _pageModel->pts[0].y, _pageModel->pts[1].x, _pageModel->pts[1].y, _pageModel->pts[2].x, _pageModel->pts[2].y, _pageModel->pts[3].x, _pageModel->pts[3].y);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	_tex.unbind();
	
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, _tweenDown.num);
	
	ofBeginShape();
	for (int i = 0; i < _pageModel->pts.size(); i++) 
	{
		ofVertex(_pageModel->pts[i].x, _pageModel->pts[i].y);
	}
	ofEndShape();
	ofDisableAlphaBlending();
}

/* Draw line from last pos to cur pos
 ___________________________________________________________ */

void PageAnimation::drawSinceLast()
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
	
	//cout << "Drawing a point" << endl;
	
	drawPoint(_curPos.x, _curPos.y);
}

/* Draw a single dot
 ___________________________________________________________ */

void PageAnimation::drawPoint(float x, float y)
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

void PageAnimation::show()
{	
	cout << "Show" << endl;
	
	_finished = false;
	
	resetBackground();
	
	_player.play();
	
	Dot * d = _drawingModel->getDotAtIndex(0);
	
	_curPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
	_lastPos.set(d->x * _tex.getWidth(), d->y * _tex.getHeight());
	
	_drawing = true;
}

void PageAnimation::hide()
{
	cout << "Hide" << endl;
	
	_tweenDown.play();
}

/* Getter / Setter
 ___________________________________________________________ */

void PageAnimation::setPageModel(Page * pageModel) 
{ 
	_pageModel = pageModel; 
}

void PageAnimation::setDrawingModel(Drawing * drawingModel) 
{ 
	_drawingModel = drawingModel; 
	_player.setModel(_drawingModel);
}


