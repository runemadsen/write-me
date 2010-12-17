#pragma once

#include "ofMain.h"
#include "Page.h"
#include "Constants.h"
#include "ofxDirList.h"

class App  
{
	
public:
	
	static App * getInstance();
	
	// page models
	ofRectangle getModelBounds() { return _modelBounds; }
	void addModel(Page * model);
	bool pageModelsChanged();
	void flagPageModelsChanged();
	Page * getModelByID(int id);
	Page * getModelByIndex(int index);
	int getPageModelsSize() { return _pageModels.size(); }
	
	// drawing models
	void addModel(Drawing * model);
	
	int nextImage() { _imageCount++; return _imageCount; }
	void setImageCount(int i) { _imageCount = i; }
	void resetImageCount() { _imageCount = 0; }
	
	void removePageModel(int index);
	
	void loadModels();
	
private:
	
	vector <Drawing *> _drawingModels;
	vector <Page *> _pageModels;
	ofRectangle _modelBounds;
	
	int _imageCount;
	
	// singleton stuff
	App();  
	App(App const&){};   
	App& operator=(App const&){};
	static App* m_pInstance;
	
	bool _pageModelsChanged;
};