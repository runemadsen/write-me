#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "App.h"
#include "Animation.h"
#include "ofxFBOTexture.h"
#include "ofxVec2f.h"
#include "ofxImage.h"
#include "Drawing.h"
#include "ofQuad.h"
#include "Tween.h"
#include "RecordingHelper.h"

class DrawingController : public Animation
{
	
public:
	
	DrawingController();
	
	void update();
	void draw();
	
	void show();
	void hide();
	
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	
	void drawSinceLast();
	
	void allocateTextures();
	void resetTexture();
	
	void drawPoint(float x, float y);
	void drawSaveImage();
	
	void reset();
	
	int getLastIndex() { return ranIndex; }
	
private:
	
	bool _firstPress;
	
	void drawTexture();
	void drawMouse();
	
	ofPoint getMousePosInTexture(int x, int y);
	
	ofxFBOTexture _tex;
	
	bool _drawing;
	
	ofxVec2f _lastPos;
	ofxVec2f _curPos;
	
	ofPoint _mousePos;
	
	Tween _fader;
	
	TweenTimer _exitTimer;
	
	RecordingHelper _recorder;
	
	float _texCoords[8];
	
	int ranIndex;
};