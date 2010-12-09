#include "PageAnimationBlank.h"

/* Constructor
 ___________________________________________________________ */

PageAnimationBlank::PageAnimationBlank()
{	
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
	
}
