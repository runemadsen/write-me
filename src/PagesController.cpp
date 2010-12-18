#include "PagesController.h"

/* Constructor
 ___________________________________________________________ */

PagesController::PagesController()
{	
	_blank_page = DISABLED;
}

/* Update
 ___________________________________________________________ */

void PagesController::update()
{	
	if(App::getInstance()->pageModelsChanged()) 
	{
		createNewViews();
	}
	
	bool allFinished = true;
	
	for(int i = 0; i < _views.size(); i++)
	{
		_views[i]->update();
		
		if(_views[i]->getFinished())
		{
			_views[i]->setDrawingModel(getRandomDrawingModel());
			_views[i]->show();
		}
		else 
		{
			allFinished = false;
		}

	}
}	

/* Draw
 ___________________________________________________________ */

void PagesController::draw()
{
	for(int i = 0; i < _views.size(); i++)
	{
		_views[i]->draw();
	}
}

/* Assign models to views
 ___________________________________________________________ */

void PagesController::createNewViews()
{	
	App * app = App::getInstance();
	
	// remove all views
	for (int i = 0; i < _views.size(); i++) 
	{
		delete _views[i];
	}
	
	_views.clear();
	
	// loop through models and create views
	for (int i = 0; i < app->getPageModelsSize(); i++) 
	{		
		PageAnimation * view = new PageAnimation();
		view->setPageModel(app->getPageModelByIndex(i));
		view->setDrawingModel(getRandomDrawingModel());
		view->show();
		_views.push_back(view);
	}
}

/* Load random drawing model
 ___________________________________________________________ */

Drawing * PagesController::getRandomDrawingModel()
{
	App * app = App::getInstance();
	
	int ran = ofRandom(0, app->getDrawingModelsSize() - 1);
	
	return App::getInstance()->getDrawingModelByIndex(ran);
}

/* Show / hide
 ___________________________________________________________ */

void PagesController::show()
{
	_finished = false;
}

void PagesController::hide()
{
	_finished = true;
}
