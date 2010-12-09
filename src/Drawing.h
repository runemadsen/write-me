#pragma once

#include "Dot.h"
#include "ofMain.h"
#include "Constants.h"

class Drawing
{
	
public:
	
	Drawing();
	
	void addDot(Dot d);
	void addMouseUp(int m);
	
	void addNormDot(float x, float y);
	void addMouseUp();
	
	Dot * getDot();
	
	bool isMouseUp();
	
	void record();
	void play();
	bool isPlaying();
	
	bool isFinished();
	
	int getMouseUpsSize() { return _mouseUps.size(); }
	int getSize() { return _pts.size(); }
	Dot * getDotAtIndex(int i) { return &_pts[i]; }
	int getMouseUpAtIndex(int i ) { return _mouseUps[i]; }
	
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