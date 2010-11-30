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
	if (key == 'r') 
	{
		_recordMode = !_recordMode;
		
		if (!_recordMode) 
		{
			App::getInstance()->flagModelsChanged();
		}
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
	}
}