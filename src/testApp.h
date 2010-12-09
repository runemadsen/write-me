#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ModelPlotter.h"
#include "PagesController.h"
#include "DrawingController.h"
#include "Animation.h"
#include "ofxTabletOSX.h"

class testApp : public ofBaseApp
{	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		void changeAnimation(int i);
	
		ModelPlotter plotter;
		
		vector <Animation *> animations;
	
		int curAnimation;
	
		ofxTabletOSX tablet;
	
		void onPenDragged(ofxTabletArgs& e);
		void onPenUp(ofxTabletArgs& e);
		void onPenDown(ofxTabletArgs& e);
		void onPenEnter(ofxTabletArgs& e);
		void onPenLeave(ofxTabletArgs& e);
		void onPenMove(ofxTabletArgs& e);
};

#endif
	
