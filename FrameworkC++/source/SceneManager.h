#pragma once
#include "Object.h"
#include <vector>
using namespace std;
class SceneManager
{
public:
	static SceneManager* s_Instance;
	
	SceneManager();
	~SceneManager();
	void Update(float frameTime);
	void Render();
	void AddObject(Object *object);
	void Init();

	int currentAmountOfObj=0;
	vector<Object* > objList;
	static SceneManager* GetInstance();
};

