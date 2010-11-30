#pragma once

#include "ofMain.h"
#include "Page.h"
#include "App.h"
#include "Constants.h"

class ModelPlotter  
{
	
public:
	
	ModelPlotter();
	
	void update();
	void draw();
	
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void keyPressed(int key);
	
	void drawModel(Page * model, int color);
	
	bool getRecordMode();
	
private:
	
	bool isClickWithinModel(float xPos, float yPos);
	void deleteSelectedModel();
	
	int _selectedModel;
	int _selectedPoint;
	
	bool _recordMode;
	
	int _idCounter;
};