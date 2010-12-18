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
	
	void record();
	void stopRecording();
		
	int getMouseUpsSize() { return _mouseUps.size(); }
	int getSize() { return _pts.size(); }
	Dot * getDotAtIndex(int i) { return &_pts[i]; }
	int getMouseUpAtIndex(int i ) { return _mouseUps[i]; }
	
	void reset();
	
private:
	
	vector <Dot> _pts;
	vector <long> _mouseUps;
	
	long _drawms;

	bool _recording;
	
};