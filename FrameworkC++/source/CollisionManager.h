#pragma once
#include "Object.h"
#include "Rect.h"
#include "Circle.h"
#include "Plane.h"
#include <vector>
using namespace std;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	

	bool CheckCollisionCC(Object * a, Object * b);


	bool CheckCollisionRC(Object *a, Object *b);

	bool CheckCollsionRR(Object *a, Object *b);

	bool CheckCollision(Object *a, Object *b);



};

