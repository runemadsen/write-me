#pragma once

class Animation
{

public:
	
	Animation() 
	{
		_finished = false;
	}
	
	virtual void update() {}
	virtual void draw() {}
	virtual void show() {}
	virtual void hide() {}
	
	virtual void keyPressed(int key) {}
	virtual void mouseMoved(int x, int y) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
	
	bool getFinished() { return _finished; }
	
protected:
	
	bool _finished;
	
private:
	
};
