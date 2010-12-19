#pragma once

#include "Dot.h"
#include "ofMain.h"
#include "Constants.h"
#include "Drawing.h"
#include "ofxXmlSettings.h"
#include "App.h"

class RecordingHelper
{
	
public:
	
	RecordingHelper();
	
	void addNormDot(float x, float y);
	void addMouseUp();
	
	void record();
	void stopRecording();
	void saveRecording();
	
	void reset();
	
private:
	
	void saveModel();
	
	Drawing * _model;
	
	long _drawms;
	
	bool _recording;
	
};