#include "App.h"

/* Singleton stuff
 ___________________________________________________________ */

App * App::m_pInstance = NULL;

App * App::getInstance()
{
	if (!m_pInstance)   
		m_pInstance = new App;
	
	return m_pInstance;
}

/* Constructor
 ___________________________________________________________ */

App::App()
{
	_modelsChanged = false;
	
	//_modelBounds.x = 600;
	_modelBounds.x = (ofGetWidth() / 2) - (DRAWING_TEXTURE_SIZE / 2);
	_modelBounds.y = (ofGetHeight() / 2) - (DRAWING_TEXTURE_SIZE / 2);
	_modelBounds.width = DRAWING_TEXTURE_SIZE;
	_modelBounds.height = DRAWING_TEXTURE_SIZE;
	
	_imageCount = 0;
}


void App::flagModelsChanged() 
{ 
	// update boundingrect
	int xLeft = ofGetWidth();
	int xRight = 0;
	int yTop = ofGetHeight();
	int yBot = 0;	
	
	for (int j = 0; j < _models.size(); j++) 
	{
		for (int i = 0; i < _models[j]->pts.size(); i++) 
		{
			if(_models[j]->pts[i].x < xLeft)		xLeft = _models[j]->pts[i].x;
			else if(_models[j]->pts[i].x > xRight)	xRight = _models[j]->pts[i].x;
			
			if(_models[j]->pts[i].y < yTop)			yTop = _models[j]->pts[i].y;
			else if(_models[j]->pts[i].y > yBot)	yBot = _models[j]->pts[i].y;
			
		}
	}
	
	cout << "xLeft: " << xLeft << endl;
	cout << "xRight: " << xRight << endl;
	cout << "yTop: " << yTop << endl;
	cout << "yBot: " << yBot << endl;
	
	_modelBounds.x = xLeft;
	_modelBounds.y = yTop;
	_modelBounds.width = xRight - xLeft;
	_modelBounds.height = yBot - yTop;
	
	cout << "Bonds X: " << _modelBounds.x << endl;
	cout << "Bonds Y: " << _modelBounds.y << endl;
	cout << "Bonds Width: " << _modelBounds.width << endl;
	cout << "Bonds Height: " << _modelBounds.height << endl;
	
	_modelsChanged = true; 
}

/* Getter
 ___________________________________________________________ */

bool App::modelsChanged()
{
	if(_modelsChanged)
	{
		_modelsChanged = false;
		
		return true;
	}
	
	return false;
}

Page * App::getModelByIndex(int index)
{
	return _models[index];
}

Page * App::getModelByID(int id)
{
	for (int i = 0; i < _models.size(); i++) 
	{
		if(id == _models[i]->id)
		{
			return _models[i];
		}
	}
	
	return NULL;
}

void App::addModel(Page * model)
{
	_models.push_back(model);
}

void App::removeModel(int index)
{
	delete _models[index];
	_models.erase(_models.begin() + index);
}