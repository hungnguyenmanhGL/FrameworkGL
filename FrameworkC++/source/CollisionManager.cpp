#include "collisionmanager.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Object.h"

using namespace std;

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::CheckCollsionRR(Object *a, Object *b) 
{
	Rect *r1 = (Rect*)a;
	Rect *r2 = (Rect*)b;
	int dx1 = r1->xPos + r1->width;
	int dy1 = r1->yPos + r1->height;
	int dx2 = r2->xPos + r2->width;
	int dy2 = r2->yPos + r2->height;
	
	if (dy1<r2->yPos || dy2<r1->yPos) return false;
	if (dx1<r2->xPos || dx2<r1->xPos) return false;

	return true;
}

bool CollisionManager::CheckCollisionCC(Object *a, Object *b)
 {
	Circle* c1 = (Circle*)a;
	Circle* c2 = (Circle*)b;
	int dx = (a->xPos - b->xPos)*(a->xPos - b->xPos);
	int dy = (a->yPos - b->yPos)*(a->yPos - b->yPos);
	
	int r = (c1->radius+c2->radius)*(c1->radius + c2->radius);
	if (dx+dy<=r) return true;
	return false;
}

bool CollisionManager::CheckCollisionRC(Object *a, Object *b)
{
	Rect* r = (Rect*) a;
	Circle* c = (Circle*) b;
	int x2 = r->xPos + r->width;
	int y1 = r->yPos;
	int x1 = r->xPos ;
	int y2 = r->yPos + r->height;
	
	int xn = max(x1, min(x2, c->xPos));
	int yn = max(y1, min(y2, c->yPos));
	
	int dx = xn - c->xPos;
	int dy = yn - c->yPos;

	return ((dx*dx + dy*dy) <= c->radius*c->radius);
}



bool CollisionManager::CheckCollision(Object* a, Object* b)
{
	if (a->getType() == 1 && b->getType() == 1)
	{
		return CheckCollsionRR(a, b);
	}

	if (a->getType() == 1 && b->getType()==2) return CheckCollisionRC(a,b);

	if (a->getType() == 2 && b->getType() == 1)
	{
		
		return CheckCollisionRC(b, a);
	} 

	if (a->getType() == 2 && b->getType() == 2) return CheckCollisionCC(a,b);
}



