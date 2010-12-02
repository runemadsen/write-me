#include "ModelPlotter.h"

/* Constructor
 ___________________________________________________________ */

ModelPlotter::ModelPlotter()
{
	_recordMode = false;
	_selectedModel = DISABLED;
	_selectedPoint = DISABLED;
	
	_idCounter = 0;
}

/* Update
 ___________________________________________________________ */

void ModelPlotter::update()
{	
	
}

/* Draw
 ___________________________________________________________ */

void ModelPlotter::draw()
{	
	if(_recordMode)
	{
		for(int i = 0; i < App::getInstance()->models.size(); i++)
		{
			ofSetColor(0, 255, 0);
			
			if(i == _selectedModel)	
			{
				drawModel(App::getInstance()->models[i], 0x000FF00);
			}
			else
			{
				drawModel(App::getInstance()->models[i], 0xFF0000);
			}
		}	
	}
}

void ModelPlotter::drawModel(Page * model, int color)
{
	ofSetColor(color);
	
	for (int i = 0; i < model->pts.size(); i++) 
	{
		ofFill();
		ofCircle(model->pts[i].x, model->pts[i].y, 3);
		
		ofNoFill();
		ofCircle(model->pts[i].x, model->pts[i].y, 3);
	}
}

/* Mouse
___________________________________________________________ */

void ModelPlotter::mousePressed(int xPos, int yPos, int button)
{	
	if(_recordMode)
	{
		if(!isClickWithinModel(xPos, yPos))
		{
			if (_selectedModel == DISABLED) 
			{
				Page * model = new Page();
				model->addDefaultPoints(xPos, yPos);
				model->id = _idCounter;
				App::getInstance()->models.push_back(model);
				
				_idCounter++;
			}
			else 
			{
				_selectedModel = DISABLED;
			}
		}
	}
}

void ModelPlotter::mouseDragged(int xPos, int yPos, int button)
{
	if(_recordMode && _selectedModel != DISABLED && _selectedPoint != DISABLED)
	{
		App::getInstance()->models[_selectedModel]->pts[_selectedPoint].x = xPos;
		App::getInstance()->models[_selectedModel]->pts[_selectedPoint].y = yPos;
	}
}

/* Utilities
___________________________________________________________ */

bool ModelPlotter::isClickWithinModel(float xPos, float yPos)
{	
	for(int i = 0; i < App::getInstance()->models.size(); i++)
	{
		Page * model = App::getInstance()->models[i];
		
		for (int j = 0; j < model->pts.size(); j++) 
		{
			if(fabs(xPos - model->pts[j].x) < SELECT_MARGIN && fabs(yPos - model->pts[j].y) < SELECT_MARGIN)
			{
				_selectedModel = i;
				_selectedPoint = j;
				
				return true;
			}
		}
	}
	
	return false;
}

void ModelPlotter::deleteSelectedModel()
{
	if(_selectedModel != DISABLED)
	{
		delete App::getInstance()->models[_selectedModel];
		App::getInstance()->models.erase(App::getInstance()->models.begin() + _selectedModel);
		_selectedModel = DISABLED;
	}
}

bool ModelPlotter::getRecordMode()
{
	return _recordMode;
}

/* Key press
 ___________________________________________________________ */

void ModelPlotter::keyPressed(int key)
{	
	if(key == 'r') 
	{
		_recordMode = !_recordMode;
		
		if (!_recordMode) 
		{
			App::getInstance()->flagModelsChanged();
		}
	}
	else if(key == 'L')
	{
		loadModels();
	}
	else if(key == 'S')
	{
		saveModels();
	}
	
	if(_recordMode)
	{
		// delete
		if(key == 127)
		{
			deleteSelectedModel();
		}
		// right arrow
		else if (key == 358) 
		{
			if(_selectedModel != DISABLED && _selectedPoint != DISABLED)
			{
				App::getInstance()->models[_selectedModel]->pts[_selectedPoint].x += 1;
			}
		}
		// left arrow
		else if (key == 356) 
		{
			if(_selectedModel != DISABLED && _selectedPoint != DISABLED)
			{
				App::getInstance()->models[_selectedModel]->pts[_selectedPoint].x -= 1;
			}
		}
		// up arrow
		else if (key == 357) 
		{
			if(_selectedModel != DISABLED && _selectedPoint != DISABLED)
			{
				App::getInstance()->models[_selectedModel]->pts[_selectedPoint].y -= 1;
			}
		}
		// down arrow
		else if (key == 359) 
		{
			if(_selectedModel != DISABLED && _selectedPoint != DISABLED)
			{
				App::getInstance()->models[_selectedModel]->pts[_selectedPoint].y += 1;
			}
		}
		// d
		else if (key == 'd') 
		{
			if(_selectedModel != DISABLED)
			{
				moveModel(true, +1);
			}
		}
		// a
		else if (key == 'a') 
		{
			if(_selectedModel != DISABLED)
			{
				moveModel(true, -1);
			}
		}
		// w
		else if (key == 'w') 
		{
			if(_selectedModel != DISABLED)
			{
				moveModel(false, -1);
			}
		}
		// s
		else if (key == 's') 
		{
			if(_selectedModel != DISABLED)
			{
				moveModel(false, +1);
			}
		}
	}
}

void ModelPlotter::moveModel(bool moveX, float moveNum)
{
	for(int i = 0; i < App::getInstance()->models[_selectedModel]->pts.size(); i++)
	{
		if(moveX)
			App::getInstance()->models[_selectedModel]->pts[i].x += moveNum;
		else 
			App::getInstance()->models[_selectedModel]->pts[i].y += moveNum;
	}
}

/* Loading / Saving
 ___________________________________________________________ */

void ModelPlotter::loadModels()
{
	App * app = App::getInstance();
	
	if(_xml.loadFile(XML_FILE))
	{
		for(int i = 0; i< app->models.size(); i++)
		{
			delete app->models[i];
		}
		
		app->models.clear();
		
		if(_xml.pushTag(PAGES, 0))
		{
			for(int i = 0; i < _xml.getNumTags(PAGE); i++) 
			{
				_xml.pushTag(PAGE, i);
				
				Page * page = new Page();
				page->id = _idCounter;
				
				for(int j = 0; j < _xml.getNumTags(POINT); j++) 
				{
					float x = (float) _xml.getAttribute(POINT, X, 0, j);
					float y = (float) _xml.getAttribute(POINT, Y, 0, j);
					
					cout << "X: " << x << endl;
					cout << "Y: " << y << endl;
					
					page->pts.push_back(ofxVec2f(x, y));
				}
				
				_xml.popTag();
				
				app->models.push_back(page);
				
				_idCounter++;
			}
			
			_xml.popTag();
		}
	}
	
	app->flagModelsChanged();
	
	cout << ":::::::::::: Models were loaded ::::::::::::" << endl;
}

void ModelPlotter::saveModels()
{	
	App * app = App::getInstance();
	
	_xml.clear();
	
	_xml.addTag(PAGES);
	_xml.pushTag(PAGES, 0);
	
	for(int i = 0; i < app->models.size(); i++)
	{
		_xml.addTag(PAGE);
		_xml.pushTag(PAGE, i);
		
		for (int j = 0; j < app->models[i]->pts.size(); j++) 
		{
			_xml.addTag(POINT);
			_xml.addAttribute(POINT, "x", ofToString(app->models[i]->pts[j].x, 1), j);
			_xml.addAttribute(POINT, "y", ofToString(app->models[i]->pts[j].y, 1), j);
		}
		
		_xml.popTag();
	}
	
	_xml.popTag();
		
	_xml.saveFile(XML_FILE);
	
	cout << ":::::::::::: Models were saved ::::::::::::" << endl;
}

