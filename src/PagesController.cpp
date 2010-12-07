#include "PagesController.h"

/* Constructor
 ___________________________________________________________ */

PagesController::PagesController()
{	

}

/* Update
 ___________________________________________________________ */

void PagesController::update()
{	
	if(App::getInstance()->modelsChanged()) 
	{
		assignModelsToViews();
	}
	
	bool all_finished = true;
	
	for(int i = 0; i < _views.size(); i++)
	{
		_views[i]->update();
		
		if(!_views[i]->finished)
		{
			all_finished = false;
		}
	}
	
	if(all_finished)
	{
		changePages();
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

/* Change pages
 ___________________________________________________________ */

void PagesController::changePages()
{
	// Load XML files
	ofxDirList DIR;
	DIR.allowExt("png");
	
	int numFiles = DIR.listDir(IMAGE_FOLDER);
	
	vector <string> fileNames;
	
	for(int i = 0; i < numFiles; i++)
	{
		fileNames.push_back(DIR.getName(i));
	}
	
	std::random_shuffle(fileNames.begin(), fileNames.end());
	
	int fileCounter = 0;
	
	for (int i = 0; i < _views.size(); i++) 
	{
		cout << fileNames[fileCounter] << endl;
		
		_views[i]->setAndPlay(IMAGE_FOLDER + fileNames[fileCounter], 100, 0);
		
		fileCounter++;
		
		if(fileCounter == fileNames.size())
		{
			fileCounter = 0;
			
			std::random_shuffle(fileNames.begin(), fileNames.end());
		}
	}
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
			PageAnimation * view = new PageAnimation();
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
	
	changePages();
}