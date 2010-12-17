#pragma once

#include "ofMain.h"
#include "Page.h"
#include "Drawing.h"
#include "Constants.h"
#include "ofxDirList.h"
#include "ofxXmlSettings.h"

class App  
{
	
public:
	
	static App * getInstance();
	
	// page models
	ofRectangle getModelBounds() { return _modelBounds; }
	void addPageModel(Page * model);
	Page * getPageModelByID(int id);
	Page * getPageModelByIndex(int index);
	int getPageModelsSize() { return _pageModels.size(); }
	bool pageModelsChanged();
	void flagPageModelsChanged();
	void removePageModel(int index);
	
	// drawing models
	void addDrawingModel(Drawing * model);
	Drawing * getDrawingModelByIndex(int index);
	int getDrawingModelsSize() { return _drawingModels.size(); }
	
	void loadDrawingModels();
	
private:
	
	vector <Drawing *> _drawingModels;
	vector <Page *> _pageModels;
	ofRectangle _modelBounds;
	
	void createDrawingModelFromXML(string fileName);
	
	int _imageCount;
	
	// singleton stuff
	App();  
	App(App const&){};   
	App& operator=(App const&){};
	static App* m_pInstance;
	
	bool _pageModelsChanged;
};