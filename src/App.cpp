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
}

/* Getter
 ___________________________________________________________ */

bool App::modelsChanged()
{
	_modelsChanged = !_modelsChanged;
	
	cout << "returning: " << !_modelsChanged << endl;
	
	return !_modelsChanged;
}

Page * App::getModel(int id)
{
	for (int i = 0; i < models.size(); i++) 
	{
		if(id == models[i]->id)
		{
			return models[i];
		}
	}
	
	return NULL;
}
