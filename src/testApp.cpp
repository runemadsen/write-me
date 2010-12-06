#include "testApp.h"

/* Setup
 _________________________________________________________________ */

void testApp::setup()
{
	ofSetWindowTitle("Dear...");

	ofSetFrameRate(60);
	
	ofBackground(0, 0, 0);
}

/* Update
 _________________________________________________________________ */

void testApp::update()
{
	plotter.update();
	pages.update();
}

/* Draw
 _________________________________________________________________ */

void testApp::draw()
{
	plotter.draw();
	
	if(!plotter.getRecordMode())
	{
		pages.draw();
	}
}

/* JSON
 _________________________________________________________________ */

void testApp::loadJSON()
{
	ifstream fin;
	fin.open( ofToDataPath("data.json").c_str()); 
	
	string allStrings;
	
	while(fin!=NULL) 
	{
		string str; 
		getline(fin, str);
		allStrings += str;
	}
	
	cout << "JSON: Loaded \n";
	
	parseJSON(allStrings);
}

void testApp::parseJSON(string s)
{
	cout << "JSON: Parsing \n";
	
	bool parsingSuccessful = reader.parse(s, root);
	
	if(!parsingSuccessful) 
	{
		cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
	}
	
	int totalAnswers = 0;
	
	// convert to models
	for(int i = 0; i < root.size(); i++)
	{		
		Json::Value assignment = root[i];
		
		Assignment model;
		model.number = assignment["assignment_number"].asString();
		model.title = assignment["assignment_title"].asString();
		model.description = assignment["assignment_description"].asString();
		
		cout << "Parsing: " << model.number << endl;
		
		for (int j = 0; j < assignment["assignment_answers"].size(); j++) 
		{
			Json::Value answer = assignment["assignment_answers"][j];
			
			Answer a_model;
			a_model.name = answer["name"].asString();
			a_model.user_details = answer["userdetails"].asString();
			a_model.text = answer["text"].asString();
			
			model.answers.push_back(a_model);
		}
		
		cout << ">>> Answers: " << model.answers.size() << endl;
		
		totalAnswers += model.answers.size(); 
	}
	
	cout << ":::: Total answers: " << totalAnswers << endl;
}

/* Key Events
 _________________________________________________________________ */

void testApp::keyPressed  (int key)
{
	plotter.keyPressed(key);
	
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
	else if(key == 'l')
	{
		loadJSON();
	}
}

void testApp::mouseDragged(int x, int y, int button)
{
	plotter.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button)
{
	plotter.mousePressed(x, y, button);
}

void testApp::keyReleased  (int key) {}
void testApp::mouseMoved(int x, int y ) {}
void testApp::mouseReleased(int x, int y, int button) {}
void testApp::windowResized(int w, int h) {}
