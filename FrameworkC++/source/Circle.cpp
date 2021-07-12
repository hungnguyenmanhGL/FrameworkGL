#include "Circle.h"
#include "VideoDriver.h"
#include "Circle.h"
#include <math.h>

Circle::Circle()
{
}

Circle::Circle(int x, int y, int radius, float velocity) {
	this->xPos = x;
	this->yPos = y;
	this->radius = radius;
	this->velocity = velocity;
}

Circle::Circle(int x, int y, int radius, float mass, float velocity) {
	this->xPos = x;
	this->yPos = y;
	this->radius = radius;
	this->mass  = mass;
	this->velocity = velocity;
}

int Circle::getType()
{
	return 2;
}


Circle::~Circle()
{
}

void Circle::Render() {
	VideoDriver::GetInstance() -> DrawCircle(this->xPos, this->yPos, this->radius);
}

void Circle::Update(float frameTime) {
	yPos += this->velocity*frameTime;
}

void Circle::OnMouseDown(int x, int y)
{
	canMove = false;
	prevMousePosX = x;
	prevMousePosY = y;
}

void Circle::Move(int x, int y)
{
	int deltaX = x - prevMousePosX;
	int deltaY = y - prevMousePosY;

	if (yPos + radius + deltaY <= SCREEN_H && xPos + radius + deltaX <= SCREEN_W && xPos + deltaX - radius >= 0) {
		xPos += deltaX;
		yPos += deltaY;
	}

	prevMousePosX = x;
	prevMousePosY = y;
}

void Circle::ThrowObject(int x, int y, clock_t time) {
	int deltaX = x - prevMousePosX;
	int deltaY = y - prevMousePosY;

	xPos += deltaX*2;
	yPos += deltaY*2;

	prevMousePosX = x;
	prevMousePosY = y;
}


bool Circle::insideObject(int x, int y){
	double a = (x-xPos)*(x - xPos);
	double b = (y - yPos)*(y - yPos);

	if (sqrt(a+b)<=this->radius) return true;
	return false;
}

int Circle::getRadius(){return radius;}


