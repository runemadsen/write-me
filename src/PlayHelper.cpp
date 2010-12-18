#include "PlayHelper.h"

/* Constructor
 ___________________________________________________________ */

PlayHelper::PlayHelper()
{	
	reset();
}

void PlayHelper::setModel(Drawing * model)
{
	_model = model;
	
	reset();
}

/* Playing methods
 ___________________________________________________________ */

Dot * PlayHelper::isDot()
{
	if(_finished)
	{
		return NULL;
	}
	
	Dot * curDot = NULL;
	
	long curms = ofGetElapsedTimeMillis() - _playms;
	
	for (int i = _curDot + 1; i < _model->dots.size(); i++) 
	{
		if(curms >= _model->dots[i]->ms)
		{
			curDot = _model->dots[i];
			_curDot = i;
		}
		else 
		{
			return curDot;
		}
	}
	
	if(_curDot == _model->dots.size() - 1)
	{
		_finished = true;
	}
}

bool PlayHelper::isMouseUp()
{
	long curms = ofGetElapsedTimeMillis() - _playms;
	
	bool returnVal = false;
	
	for (int i = _curMouseUp + 1; i < _model->mouseUps.size(); i++) 
	{		
		if(curms >= _model->mouseUps[i])
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

/* Play
 ___________________________________________________________ */

void PlayHelper::play()
{
	_playms = ofGetElapsedTimeMillis();
	_playing = true;
}

/* Reset
 ___________________________________________________________ */

void PlayHelper::reset()
{
	_playms = 0;
	_playing = false;
	_finished = false;
	
	_curDot = DISABLED;
	_curMouseUp = DISABLED;
}

/* Getters
 ___________________________________________________________ */

bool PlayHelper::isFinished()
{
	if (_finished) 
	{
		_playing = false;
	}
	
	return _finished;
}

bool PlayHelper::isPlaying()
{
	return _playing;
}
