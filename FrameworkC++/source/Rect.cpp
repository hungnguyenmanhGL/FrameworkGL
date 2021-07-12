#include "Rect.h"
#include "videoDriver.h"
#include "CollisionManager.h"

Rect::Rect()
{
}

Rect::Rect(int x, int y, int w, int h) {
	this->xPos = x;
	this->yPos = y;
	this->width = w;
	this->height = h;
}

Rect::Rect(int x, int y, int w, int h, float m, float v) {
	this->xPos = x;
	this->yPos = y;
	this->width = w;
	this->height = h;
	this->mass = m;
	this->velocity = v;
}

Rect::Rect(int x, int y, int w, int h, float v) {
	this->xPos = x;
	this->yPos = y;
	this->width = w;
	this->height = h;
	this->velocity = v;
}


Rect::~Rect()
{
}

void Rect::Render()
{
	VideoDriver::GetInstance()->DrawRect(this->xPos, this->yPos, this->width, this->height);
}

void Rect::Update(float frameTime)
{
	
	yPos += this->velocity*frameTime;

}

void Rect::OnMouseDown(int x, int y)
{
	canMove = false;
	prevMousePosX = x;
	prevMousePosY = y;
}

bool Rect::insideObject(int x, int y) {
	if (x>=this->xPos && x<=(this->xPos+this->width) && y >= this->yPos && y <= (this->yPos + this->height)) return true;
	return false;
}

void Rect::Move(int x, int y)
{
	int deltaX = x - prevMousePosX;
	int deltaY = y - prevMousePosY;

	if (yPos + deltaY + height <= SCREEN_H && xPos + deltaX + width <= SCREEN_W && xPos + deltaX >=0) {
		xPos += deltaX;
		yPos += deltaY;
	}
	prevMousePosX = x;
	prevMousePosY = y;
}

void Rect::ThrowObject(int x, int y, clock_t time) {
	int deltaX = x - prevMousePosX;
	int deltaY = y - prevMousePosY;

	xPos += (deltaX / time) * 100;
	yPos += (deltaY / time) * 100;

	prevMousePosX = x;
	prevMousePosY = y;
}


int Rect::getType()
{
	return 1;
}

int Rect::getWidth()
{
	return width;
}

int Rect::getHeight(){return height;}

