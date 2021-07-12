#pragma once
#include "Object.h"
class Plane :public Object
{
public:
	int xPos;
	int yPos;
	int height;
	int width;
	int mass;
	Plane();
	Plane(int x, int y, int h, int w, int m);
	Plane(int x, int y, int h, int w);
	~Plane();
	bool insideObject(int x, int y);
	int getType();
	bool canMove = false;
	void Render();
	void Move(int x, int y);
};

