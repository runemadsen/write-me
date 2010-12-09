#pragma once

#include "Dot.h"
#include "ofMain.h"
#include "Constants.h"

class Drawing
{
	
public:
	
	Drawing();
	
	void addNormDot(float x, float y);
	void addMouseUp();
	
	Dot * getDot();
	
	bool isMouseUp();
	
	void play();
	bool isPlaying();
	
	bool isFinished();
	
	
	
private:
	
	vector <Dot> _pts;
	vector <long> _mouseUps;
	
	long _drawms;
	long _playms;
	
	bool _finished;
	bool _playing;
	
	int _curDot;
	int _curMouseUp;
	
};