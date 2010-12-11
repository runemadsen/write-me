#include "Drawing.h"

/* Constructor
 ___________________________________________________________ */

Drawing::Drawing()
{
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

/* Playing methods
 ___________________________________________________________ */

void Drawing::addNormDot(float x, float y)
{
	Dot d;
	d.x = x;
	d.y = y;
	d.ms = ofGetElapsedTimeMillis() - _drawms;
	_pts.push_back(d);
}

Dot * Drawing::getDot()
{
	if(_finished)
	{
		return NULL;
	}
	
	Dot * curDot = NULL;
	
	long curms = ofGetElapsedTimeMillis() - _playms;
	
	for (int i = _curDot + 1; i < _pts.size(); i++) 
	{
		if(curms >= _pts[i].ms)
		{
			curDot = &_pts[i];
			_curDot = i;
		}
		else 
		{
			return curDot;
		}
	}
	
	if(_curDot == _pts.size() - 1)
	{
		_finished = true;
	}
}

void Drawing::addMouseUp()
{
	_mouseUps.push_back(ofGetElapsedTimeMillis() - _drawms);
}

bool Drawing::isMouseUp()
{
	long curms = ofGetElapsedTimeMillis() - _playms;
	
	bool returnVal = false;
	
	for (int i = _curMouseUp + 1; i < _mouseUps.size(); i++) 
	{		
		if(curms >= _mouseUps[i])
		{
			returnVal = true;
			_curMouseUp = i;
		}
		else 
		{
			return returnVal;
		}
	}
}

/* Record
 ___________________________________________________________ */

void Drawing::record()
{
	_drawms = ofGetElapsedTimeMillis();
}

/* Play
 ___________________________________________________________ */

void Drawing::play()
{
	_playms = ofGetElapsedTimeMillis();
	_playing = true;
}

/* Reset
 ___________________________________________________________ */

void Drawing::reset()
{
	_drawms = 0;
	_playing = false;
	_finished = false;
	
	_curDot = DISABLED;
	_curMouseUp = DISABLED;
	
	_pts.erase(_pts.begin(), _pts.end());
}

/* Getters
 ___________________________________________________________ */

bool Drawing::isFinished()
{
	if (_finished) 
	{
		_playing = false;
	}
	return _finished;
}

bool Drawing::isPlaying()
{
	return _playing;
}
