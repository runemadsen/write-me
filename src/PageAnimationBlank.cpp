#include "PageAnimationBlank.h"

/* Constructor
 ___________________________________________________________ */

PageAnimationBlank::PageAnimationBlank()
{	
	modelid = DISABLED;
}

/* Update
 ___________________________________________________________ */

void PageAnimationBlank::update()
{	
	_tween.update();
	
	if(_tween.finished())
	{
		_finished = true;
	}
}

/* Draw
 ___________________________________________________________ */

void PageAnimationBlank::draw()
{	
	Page * model = App::getInstance()->getModelByID(modelid);
}
