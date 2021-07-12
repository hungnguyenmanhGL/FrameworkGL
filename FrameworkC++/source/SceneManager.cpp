#include "SceneManager.h"
#include <iostream>
#include <cstdio>
#include "Object.h"
#include "Rect.h"
#include "Circle.h"
#include<string>

#include "videoDriver.h"
using namespace std;

SceneManager* SceneManager::s_Instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Update(float frameTime)
{
	
	VideoDriver::GetInstance()->CleanScreen();
	Render();
	for (int i = 0; i < objList.size(); i++) {
		//objList.at(i)->ThrowObject();
		if (objList.at(i)->canMove && !objList.at(i)->reachedBottom && !objList.at(i)->isSelected){
		objList.at(i)->Update(frameTime); 
		}
	}
}

void SceneManager::Render()
{
	for (int i = 0; i < objList.size(); i++)
	{
		objList.at(i)->Render();
	}
}

void SceneManager::AddObject(Object *object)
{
	this->objList.push_back(object);
}

void SceneManager::Init()
{
	FILE *file;
	file = fopen("SceneManager.txt", "r+");
	int num;
	fscanf(file, "#OBJECT_NUM %d\n", &num);
	cout<< num << endl;

	for (int i = 0; i < num; i++) {
		int id;
		char type[10];
		fscanf(file, "#ID: %d\n", &id);
		fscanf(file, "TYPE: %s\n", &type);
		cout << type << endl;
		if (strcmp(type, "RECT") == 0 ) {
			int x; int y;
			int w; int h;
			float ve;
			fscanf(file, "POSITION: %d, %d, %d, %d\n", &x, &y, &w, &h);
			fscanf(file, "VELOCITY: %f\n", &ve);
			cout << x << " " << y << " " << w << " " << h << endl;

			Object *r = new Rect(x, y, w, h, ve);
			//cout << r->xPos << " " << r->yPos << endl;
			this->AddObject(r);
			//cout << r->xPos << " " << r->yPos << endl;
		}

		if (strcmp(type, "CIRCLE") == 0){
			int x; int y;
			int ra;
			float ve;
			fscanf(file, "POSITION: %d, %d, %d\n", &x,&y,&ra);
			fscanf(file, "VELOCITY: %f\n", &ve);
			cout << x << " " << y << " " <<ra << " " << ve << endl;
			Circle *c = new Circle(x,y,ra,ve);
			this->AddObject(c);
		}
	}
	fclose(file);

	
}

/*SceneManager.txt example
#OBJECT_NUM 4
#ID 0
TYPE: RECT
	POSITION : 100, 70, 100, 100
	VELOCITY : 203
	#ID 1
	TYPE: CIRCLE
	POSITION : 120, 300, 50
	VELOCITY : 10
	#ID 2
	TYPE: RECT
	POSITION : 400, 400, 150, 100
	VELOCITY : 5
	#ID 3
	TYPE: RECT
	POSITION : 400, 400, 100, 150
	VELOCITY : 5*/