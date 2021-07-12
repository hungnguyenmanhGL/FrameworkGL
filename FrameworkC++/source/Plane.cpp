#include "Plane.h"
#include "videoDriver.h"


Plane::Plane()
{
}

Plane::Plane(int x, int y, int h, int w, int m)
{
	this->xPos = x;
	this->yPos = y;
	this->height = height;
	this->width = width;
	this->mass = m;
}

Plane::Plane(int x, int y, int h, int w)
{
	this->xPos = x;
	this->yPos = y;
	this->height = height;
	this->width = width;
}


Plane::~Plane()
{
}

void Plane::Render()
{
	VideoDriver::GetInstance()->DrawRect(this->xPos, this->yPos, this->height,this->width);
}

void Plane::Move(int x, int y)
{
}

bool Plane::insideObject(int x, int y)
{
	return false;
}

int Plane::getType()
{
	return 3;
}
