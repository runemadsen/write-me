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
	_pageModelsChanged = false;
	
	//_modelBounds.x = 600;
	_modelBounds.x = (ofGetWidth() / 2) - (DRAWING_TEXTURE_SIZE / 2);
	_modelBounds.y = (ofGetHeight() / 2) - (DRAWING_TEXTURE_SIZE / 2);
	_modelBounds.width = DRAWING_TEXTURE_SIZE;
	_modelBounds.height = DRAWING_TEXTURE_SIZE;
	
	_imageCount = 0;
}

/* Flag models changed
 ___________________________________________________________ */

void App::flagPageModelsChanged() 
{ 
	// update boundingrect
	int xLeft = ofGetWidth();
	int xRight = 0;
	int yTop = ofGetHeight();
	int yBot = 0;	
	
	for (int j = 0; j < _pageModels.size(); j++) 
	{
		for (int i = 0; i < _pageModels[j]->pts.size(); i++) 
		{
			if(_pageModels[j]->pts[i].x < xLeft)		xLeft = _pageModels[j]->pts[i].x;
			else if(_pageModels[j]->pts[i].x > xRight)	xRight = _pageModels[j]->pts[i].x;
			
			if(_pageModels[j]->pts[i].y < yTop)			yTop = _pageModels[j]->pts[i].y;
			else if(_pageModels[j]->pts[i].y > yBot)	yBot = _pageModels[j]->pts[i].y;
			
		}
	}

	_modelBounds.x = xLeft;
	_modelBounds.y = yTop;
	_modelBounds.width = xRight - xLeft;
	_modelBounds.height = yBot - yTop;
	
	_pageModelsChanged = true; 
}

/* Load Models
 ___________________________________________________________ */

void App::loadModels()
{
	
}

/* Getters
 ___________________________________________________________ */

bool App::pageModelsChanged()
{
	if(_pageModelsChanged)
	{
		_pageModelsChanged = false;
		
		return true;
	}
	
	return false;
}

Page * App::getModelByIndex(int index)
{
	return _pageModels[index];
}

Page * App::getModelByID(int id)
{
	for (int i = 0; i < _pageModels.size(); i++) 
	{
		if(id == _pageModels[i]->id)
		{
			return _pageModels[i];
		}
	}
	
	return NULL;
}

/* Setters
 ___________________________________________________________ */

void App::addModel(Page * model)
{
	_pageModels.push_back(model);
}

void App::removePageModel(int index)
{
	delete _pageModels[index];
	_pageModels.erase(_pageModels.begin() + index);
}