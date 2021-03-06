#include "PageAnimationImage.h"

/* Constructor
 ___________________________________________________________ */

PageAnimationImage::PageAnimationImage()
{	
	modelid = DISABLED;
}

/* Update
 ___________________________________________________________ */

void PageAnimationImage::update()
{	
	_tween.update();
	
	if(_tween.finished())
	{
		_finished = true;
	}
}

/* Draw
 ___________________________________________________________ */

void PageAnimationImage::draw()
{	
	Page * model = App::getInstance()->getModelByID(modelid);
	
	ofFill();
	ofSetColor(255, 255, 255);
	
	_img.getTextureReference().bind();
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad2D(model->pts[0].x, model->pts[0].y, model->pts[1].x, model->pts[1].y, model->pts[2].x, model->pts[2].y, model->pts[3].x, model->pts[3].y);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	_img.getTextureReference().unbind();
}

/* Set new image
 ___________________________________________________________ */

void PageAnimationImage::setAndPlay(string img, int duration, int delay)
{	
	reset();
	
	_img.loadImage(img);
	
	_texCoords[0] = 0;
	_texCoords[1] = 0;
	
	_texCoords[2] = _img.getWidth();
	_texCoords[3] = 0;
	
	_texCoords[4] = _img.getWidth();
	_texCoords[5] = _img.getHeight(); 
	
	_texCoords[6] = 0;
	_texCoords[7] = _img.getHeight();
	
	_tween.setup(duration, 0, duration, Easing::LinearEaseIn, delay);
	
	_tween.play();
}

/* Reset
 ___________________________________________________________ */

void PageAnimationImage::reset()
{
	_finished = false;
	_tween.stop();
}
