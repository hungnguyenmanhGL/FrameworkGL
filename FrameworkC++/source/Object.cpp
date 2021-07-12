#include "Object.h"
#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

void Object::Render(){}
void Object::Update(float frameTime){}

void Object::OnMouseDown(int x, int y)
{
	canMove = false;
}

void Object::Move(int x, int y)
{
}

void Object::ThrowObject()
{
	xPos += 10;
	yPos += 10;
}

int Object::getType() {
	return -1;
}







