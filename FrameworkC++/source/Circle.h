#pragma once
#include "Object.h"
class Circle :
	public Object


{
private:
	int prevMousePosX;
	int prevMousePosY;

public:
	Circle();
	Circle(int x, int y, int radius, float velocity);
	Circle(int x, int y, int radius, float mass, float velocity);
	int getType();
	~Circle();
	void Render();
	void Update(float frameTime);
	void Move(int x, int y);
	void ThrowObject(int x, int y, clock_t time);
	bool insideObject(int x, int y);
	void OnMouseDown(int x, int y);
	int getRadius();
	
	bool reachBottom = false;  
	int radius;
	
	
	
};

