#pragma once

#include "ofMain.h"
#include "Page.h"

class App  
{
	
public:
	
	static App * getInstance();
	
	vector <Page *> models;
	
	bool modelsChanged();
	void flagModelsChanged() { _modelsChanged = true; }
	
	Page * getModel(int id);
	
private:
	
	// singleton stuff
	App();  
	App(App const&){};   
	App& operator=(App const&){};
	static App* m_pInstance;
	
	bool _modelsChanged;
};