#pragma once
#include "Object.h"
class Rect :
	public Object
{
private:
	int prevMousePosX;
	int prevMousePosY;

public:
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(int x, int y, int w, int h, float m, float v);
	Rect(int x, int y, int w, int h, float v);
	~Rect();
	void Render();
	void Update(float frameTime);
	void OnMouseDown(int x, int y);
	bool insideObject(int x, int y);
	void Move(int x, int y);
	void ThrowObject(int x, int y, clock_t time);
	int getType();
	int getWidth();
	int getHeight();
	int xPos;
	int yPos;
	int height;
	int width;
	bool reachBottom = false;
	
};

