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

/* Playing methods
 ___________________________________________________________ */

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
