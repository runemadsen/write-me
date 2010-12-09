#pragma once

#include "ofMain.h"
#include "Page.h"
#include "Constants.h"
#include "ofxDirList.h"

class App  
{
	
public:
	
	static App * getInstance();
	
	void addModel(Page * model);
	
	ofRectangle getModelBounds() { return _modelBounds; }
	
	bool modelsChanged();
	
	int nextImage() { _imageCount++; return _imageCount; }
	void setImageCount(int i) { _imageCount = i; }
	void resetImageCount() { _imageCount = 0; }
	
	void flagModelsChanged();
	
	Page * getModelByID(int id);
	Page * getModelByIndex(int index);
	int getModelsSize() { return _models.size(); }
	
	void removeModel(int index);
	
private:
	
	vector <Page *> _models;
	ofRectangle _modelBounds;
	
	int _imageCount;
	
	// singleton stuff
	App();  
	App(App const&){};   
	App& operator=(App const&){};
	static App* m_pInstance;
	
	bool _modelsChanged;
};