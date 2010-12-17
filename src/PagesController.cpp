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
		PageAnimation * view = new PageAnimationDrawing();
		view->setPageModel(app->getModelByIndex(i));
		view->setDrawingModel(getRandomDrawingModel());
		view->show();
		_views.push_back(view);
	}
}

/* Load random drawing model
 ___________________________________________________________ */

Drawing PagesController::getRandomDrawingModel()
{
	ofxDirList DIR;
	DIR.allowExt("xml");
	
	int numFiles = DIR.listDir(DRAWING_FOLDER);
	
	vector <string> fileNames;
	
	int ranIndex = ofRandom(0, numFiles);
	
	Drawing drawing;
	
	if(_xml.loadFile(DRAWING_FOLDER + DIR.getName(ranIndex)))
	{
		if(_xml.pushTag(DRAWING, 0))
		{
			// points
			if(_xml.pushTag(POINTS, 0))
			{
				for (int i = 0; i < _xml.getNumTags(POINT); i++) 
				{
					Dot d;
					d.x = (float) _xml.getAttribute(POINT, X, 0.0, i);
					d.y = (float) _xml.getAttribute(POINT, Y, 0.0, i);
					d.ms = (long) _xml.getAttribute(POINT, MS, 0, i);
					
					drawing.addDot(d);
				}
				
				_xml.popTag();
			}
			
			// mouse ups
			if(_xml.pushTag(MOUSE_UPS, 0))
			{
				for (int i = 0; i < _xml.getNumTags(MOUSE_UP); i++) 
				{
					drawing.addMouseUp( (long) _xml.getAttribute(MOUSE_UP, MS, 0, i));
				}
				
				_xml.popTag();
			}
			
			_xml.popTag();
		}
	}
	
	return drawing;
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
