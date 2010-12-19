#include "RecordingHelper.h"

/* Constructor
 ___________________________________________________________ */

RecordingHelper::RecordingHelper()
{
	_recording = false;
	
	reset();
}

/* Recording methods
 ___________________________________________________________ */

void RecordingHelper::addMouseUp()
{
	if(_recording)
	{
		_model->mouseUps.push_back(ofGetElapsedTimeMillis() - _drawms);
	}
}

void RecordingHelper::addNormDot(float x, float y)
{
	if(_recording)
	{
		Dot * d = new Dot();
		d->x = x;
		d->y = y;
		d->ms = ofGetElapsedTimeMillis() - _drawms;
		_model->dots.push_back(d);
	}
}

/* Record
 ___________________________________________________________ */

void RecordingHelper::record()
{
	_model = new Drawing();
	
	_recording = true;
	_drawms = ofGetElapsedTimeMillis();
}

void RecordingHelper::stopRecording()
{
	_recording = false;
	
	reset();
}

void RecordingHelper::saveRecording()
{
	if(ENABLE_SAVE)
	{
		if (_model->dots.size() > 0) 
		{
			saveModel();
			
			App::getInstance()->addDrawingModel(_model);
		}
	}
}

/* Save Model
 ___________________________________________________________ */

void RecordingHelper::saveModel()
{	
	ofxXmlSettings xml;
	
	xml.loadFromBuffer("<root></root>");
	
	xml.clear();
	
	xml.addTag(DRAWING);
	xml.pushTag(DRAWING, 0);
	
	xml.addTag(POINTS);
	xml.pushTag(POINTS, 0);
	
	for(int i = 0; i < _model->dots.size(); i++)
	{
		xml.addTag(POINT);
		xml.addAttribute(POINT, X, ofToString(_model->dots[i]->x, 2), i);
		xml.addAttribute(POINT, Y, ofToString(_model->dots[i]->y, 2), i);
		xml.addAttribute(POINT, MS, ofToString(_model->dots[i]->ms, 0), i);
	}
	
	xml.popTag();
	
	xml.addTag(MOUSE_UPS);
	xml.pushTag(MOUSE_UPS, 0);
	
	for(int i = 0; i < _model->mouseUps.size(); i++)
	{
		xml.addTag(MOUSE_UP);
		xml.addAttribute(MOUSE_UP, MS, ofToString(_model->mouseUps[i], 0), i);
	}
	
	xml.popTag();
	
	string file = ofToString(ofGetYear());
	file += "-";
	file += ofToString(ofGetMonth());
	file += "-";
	file += ofToString(ofGetDay());
	file += "-";
	file += ofToString(ofGetHours());
	file += "-";
	file += ofToString(ofGetMinutes());
	file += "-";
	file += ofToString(ofGetSeconds());
	
	xml.saveFile(DRAWING_FOLDER + file + ".xml");
}


/* Reset
 ___________________________________________________________ */

void RecordingHelper::reset()
{
	_drawms = 0;
}
