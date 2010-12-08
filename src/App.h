#pragma once

#include "ofMain.h"
#include "Page.h"
#include "Constants.h"

class App  
{
	
public:
	
	static App * getInstance();
	
	void addModel(Page * model);
	
	ofRectangle getModelBounds() { return _modelBounds; }
	
	bool modelsChanged();
	
	void flagModelsChanged();
	
	Page * getModelByID(int id);
	Page * getModelByIndex(int index);
	int getModelsSize() { cout << "Size: " << _models.size() << endl; return _models.size(); }
	
	void removeModel(int index);
	
private:
	
	vector <Page *> _models;
	ofRectangle _modelBounds;
	
	// singleton stuff
	App();  
	App(App const&){};   
	App& operator=(App const&){};
	static App* m_pInstance;
	
	bool _modelsChanged;
};