#pragma once

#include "Dot.h"
#include "ofMain.h"
#include "Constants.h"
#include "Drawing.h"

class PlayHelper
{
	
public:
	
	PlayHelper();
	
	void setModel(Drawing * model);
	
	Dot * isDot();
	
	bool isMouseUp();
	
	void play();
	
	bool isPlaying();
	bool isFinished();
	
	void reset();
	
private:

	long _playms;
	bool _finished;
	bool _playing;
	
	int _curDot;
	int _curMouseUp;
	
	Drawing * _model;
};