#include "PageView.h"

PageView::PageView()
{
	// update texcoords
	_texCoords[0] = 0;
	_texCoords[1] = 0;
	
	_texCoords[2] = 300;
	_texCoords[3] = 0;
	
	_texCoords[4] = 300;
	_texCoords[5] = 300;
	
	_texCoords[6] = 0;
	_texCoords[7] = 300;
}

void PageView::update()
{

}

void PageView::draw()
{
	Page * model = App::getInstance()->getModel(modelid);
	
	/*ofSetColor(0, 0, 255);

	for (int i = 0; i < model->pts.size(); i++) 
	{
		ofFill();
		ofCircle(model->pts[i].x, model->pts[i].y, 3);
		ofNoFill();
		ofCircle(model->pts[i].x, model->pts[i].y, 3);
		
		if(i < model->pts.size() - 1)	ofLine(model->pts[i].x, model->pts[i].y, model->pts[i + 1].x, model->pts[i + 1].y);
		else							ofLine(model->pts[i].x, model->pts[i].y, model->pts[0].x, model->pts[0].y);		
	}*/
	
	ofFill();
	ofSetColor(255, 255, 255);
	
	// draw video (remember to bind before (done in cellscontroller))
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad3D(model->pts[0].x, model->pts[0].y, 0, model->pts[1].x, model->pts[1].y, 0, model->pts[2].x, model->pts[2].y, 0, model->pts[3].x, model->pts[3].y, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}