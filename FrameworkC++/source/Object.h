#pragma once
#include <string>
#include <cstring>
#include <ctime>
using namespace std;
class Object
{
public:
	Object();
	~Object();
	virtual void Render();
	virtual void Update(float frameTime);
	virtual void OnMouseDown(int x, int  y);
	virtual void Move(int x, int y);
	virtual void ThrowObject();
	virtual bool insideObject(int x, int y) =0;

	virtual int getType() ;
	int xPos;
	int yPos;
	clock_t t;
	float mass;
	float velocity;
	int shape;
	int a; 
	bool canMove = true;
	bool isSelected = false;
	bool reachedBottom = false;
	bool hasCollided = false;
};

