#include "Drawing.h"

/* Constructor
 ___________________________________________________________ */

Drawing::Drawing()
{
	_recording = false;
	
	reset();
}

/* Load methods
 ___________________________________________________________ */

void Drawing::addDot(Dot d)
{
	_pts.push_back(d);
}

void Drawing::addMouseUp(int m)
{
	_mouseUps.push_back(m);
}

/* Recording methods
 ___________________________________________________________ */

void Drawing::addMouseUp()
{
	if(_recording)
	{
		_mouseUps.push_back(ofGetElapsedTimeMillis() - _drawms);
	}
}

void Drawing::addNormDot(float x, float y)
{
	if(_recording)
	{
		Dot d;
		d.x = x;
		d.y = y;
		d.ms = ofGetElapsedTimeMillis() - _drawms;
		_pts.push_back(d);
	}
}

/* Record
 ___________________________________________________________ */

void Drawing::record()
{
	_recording = true;
	_drawms = ofGetElapsedTimeMillis();
}

void Drawing::stopRecording()
{
	_recording = false;
	
	reset();
}

/* Reset
 ___________________________________________________________ */

void Drawing::reset()
{
	_drawms = 0;
}
