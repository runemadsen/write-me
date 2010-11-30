#include "PagesController.h"

/* Constructor
 ___________________________________________________________ */

PagesController::PagesController()
{
	testVid.loadMovie("test.mov");
	testVid.play();
}

/* Update
 ___________________________________________________________ */

void PagesController::update()
{	
	testVid.update();
	
	if(App::getInstance()->modelsChanged()) 
	{
		assignModelsToViews();
	}
	
	for(int i = 0; i < _views.size(); i++)
	{
		_views[i]->update();
	}
}	

/* Draw
 ___________________________________________________________ */

void PagesController::draw()
{
	testVid.getTextureReference().bind();
	
	for(int i = 0; i < _views.size(); i++)
	{
		_views[i]->draw();
	}
	
	testVid.getTextureReference().unbind();
}

/* Reset
 ___________________________________________________________ */

void PagesController::assignModelsToViews()
{
	// loop through models to check views
	for (int i = 0; i < App::getInstance()->models.size(); i++) 
	{
		Page * model = App::getInstance()->models[i];
		
		bool found = false;
		
		for (int j = 0; j < _views.size(); j++) 
		{
			if(model->id == _views[j]->modelid)
			{
				found = true;
			}
		}
		
		if(!found)
		{
			PageView * view = new PageView();
			view->modelid = model->id;
			_views.push_back(view);
		}
	}
	
	// loop through views to check models
	for (int i = 0; i < _views.size(); i++) 
	{
		bool keep = false;
		
		for (int j = 0; j < App::getInstance()->models.size(); j++) 
		{
			if(_views[i]->modelid == App::getInstance()->models[j]->id)
			{
				keep = true;
			}
		}
		
		if(!keep)
		{
			delete _views[i];
			_views.erase(_views.begin() + i);
		}
	}
}