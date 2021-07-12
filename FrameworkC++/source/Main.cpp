#include <stdio.h>
#include "esUtil.h"
#include "log.h"
#include "define.h"
#include "VideoDriver.h"
#include <crtdbg.h>
#include "Circle.h"
#include "Object.h"
#include "SceneManager.h"
#include "Rect.h"
#include "Plane.h"
#include <iostream>
#include "CollisionManager.h"
#include <ctime>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
CollisionManager cm = CollisionManager();
clock_t t;

void PaintObject()
{
	// Limit FPS
	DWORD start, end;
	start = GetTickCount();

	// Render something here
	VideoDriver::GetInstance()->CleanScreen();
	VideoDriver::GetInstance()->DrawLine(1,1, SCREEN_W-1, 1);
	VideoDriver::GetInstance()->DrawLine(SCREEN_W-1, 1, SCREEN_W - 1, SCREEN_H-1);
	VideoDriver::GetInstance()->DrawLine(1, 1, 1, SCREEN_H - 1);
	VideoDriver::GetInstance()->DrawLine(0, SCREEN_H-1, SCREEN_W - 1, SCREEN_H - 1);
	//VideoDriver::GetInstance()->DrawCircle(100.0f, 100.0f, 100.0f);
	//VideoDriver::GetInstance()->FillRect(0, 0, 100, 100);
	//a->Render();
	//wall ->Render();
	SceneManager::GetInstance()->Render();
	//re->Render();
	//re2->Render();
	// Limit FPS
	end = GetTickCount();
	DWORD frameTime = end - start;
	if (frameTime < 1000.0/LIMIT_FPS)
		Sleep(1000/LIMIT_FPS - frameTime);
}

bool InitGraphics(int w, int h)
{
	// Init scene
	LOGI("Initializing...");
	glViewport(0, 0, w, h);
	LOGI("Done!");
	SceneManager::GetInstance()->Init();
	return true;
}

void TouchActionDown(ESContext *esContext,int x, int y)
{
	// Mouse down
	t = clock();
	for (int i = 0; i < SceneManager::GetInstance()->objList.size(); i++) 
	{
		
		if (SceneManager::GetInstance()->objList.at(i)->getType() == 1 && SceneManager::GetInstance()->objList.at(i)->insideObject(x,y) )
		{
			SceneManager::GetInstance()->objList.at(i)->OnMouseDown(x, y);
			SceneManager::GetInstance()->objList.at(i)->isSelected = true;
			break;
		} 
		if (SceneManager::GetInstance()->objList.at(i)->getType() == 2 && SceneManager::GetInstance()->objList.at(i)->insideObject(x,y) ) 
		{
			/*SceneManager::GetInstance()->objList.at(i)->canMove = false;*/
			SceneManager::GetInstance()->objList.at(i)->OnMouseDown(x, y);
			SceneManager::GetInstance()->objList.at(i)->isSelected = true;
			break;
		}
	}
}


void TouchActionUp(ESContext *esContext,int x, int y)
{
	// Mouse up
	t = clock() - t;
	for (int i = 0; i < SceneManager::GetInstance()->objList.size(); i++)
	{
		
			//SceneManager::GetInstance()->objList.at(i)->canMove = true;
			SceneManager::GetInstance()->objList.at(i)->isSelected = false;
			SceneManager::GetInstance()->objList.at(i)->t = clock();
		
	}
}

void TouchActionMove(ESContext *esContext,int x, int y)
{
	// Mouse move
	for (int i = 0; i < SceneManager::GetInstance()->objList.size(); i++)
	{
		if (SceneManager::GetInstance()->objList.at(i)->insideObject(x, y) && SceneManager::GetInstance()->objList.at(i)->isSelected==true)
		{
			SceneManager::GetInstance()->objList.at(i)->Move(x,y);
			//SceneManager::GetInstance()->objList.at(i)->ThrowObject(x,y,t);
		}
	}
}

void KeyDown(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':
	case 'w':
		break;
	case 'S':
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	}
}

void KeyUp(ESContext *ESContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':
	case 'w':
		break;
	case 'S':
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	}
}

void GameUpdate(ESContext *esContext, float deltaTime)
{
	// Update scene
	
	SceneManager::GetInstance()->Update(0.1);
	
	for (int i = 0; i < SceneManager::GetInstance()->objList.size() - 1; i++)
	{
		for (int j = i + 1; j < SceneManager::GetInstance()->objList.size(); j++) {

			if (!cm.CheckCollision(SceneManager::GetInstance()->objList.at(i), SceneManager::GetInstance()->objList.at(j)) && !SceneManager::GetInstance()->objList.at(i)->isSelected)
			{

				SceneManager::GetInstance()->objList.at(i)->canMove = true;
			}
			if (!cm.CheckCollision(SceneManager::GetInstance()->objList.at(i), SceneManager::GetInstance()->objList.at(j)) && !SceneManager::GetInstance()->objList.at(j)->isSelected)
			{

				SceneManager::GetInstance()->objList.at(j)->canMove = true;

			}
		}
	}

	for (int i = 0; i < SceneManager::GetInstance()->objList.size() ; i++)
	{
		if (SceneManager::GetInstance()->objList.at(i)->getType() == 2) {
			Circle *c = (Circle*)SceneManager::GetInstance()->objList.at(i);
			if (c->radius + c->yPos >= SCREEN_H) 
			{
				//cout << "Edge collision detected" << endl;
				SceneManager::GetInstance()->objList.at(i)->reachedBottom = true;
			}
			else
			{
				SceneManager::GetInstance()->objList.at(i)->reachedBottom = false;
			}
		}

		if (SceneManager::GetInstance()->objList.at(i)->getType() == 1) {
			Rect *r = (Rect*)SceneManager::GetInstance()->objList.at(i);
			if (r->height + r->yPos >= SCREEN_H)
			{	
				//cout << "Edge collision detected" << endl;
				SceneManager::GetInstance()->objList.at(i)->reachedBottom = true;
			} 
			else
			{
				//cout << r->yPos << endl;
				SceneManager::GetInstance()->objList.at(i)->reachedBottom = false;
			}
		}
	}

	for (int i = 0; i < SceneManager::GetInstance()->objList.size() - 1; i++)
	{
		for (int j = i+1; j < SceneManager::GetInstance()->objList.size(); j++) 
		{
			if (cm.CheckCollision(SceneManager::GetInstance()->objList.at(i), SceneManager::GetInstance()->objList.at(j)))
			{
				if (SceneManager::GetInstance()->objList.at(i)->getType() == 2 && SceneManager::GetInstance()->objList.at(j)->getType() == 1)
				{
					Rect* r = (Rect*)SceneManager::GetInstance()->objList.at(j);
					if (SceneManager::GetInstance()->objList.at(i)->yPos >= r->yPos)
					{
						SceneManager::GetInstance()->objList.at(j)->canMove = false;
						SceneManager::GetInstance()->objList.at(i)->canMove = true;
					}
					else{ 
						SceneManager::GetInstance()->objList.at(j)->canMove = true;
						SceneManager::GetInstance()->objList.at(i)->canMove = false;
					}
				}
				

				if (SceneManager::GetInstance()->objList.at(i)->getType() == 1 && SceneManager::GetInstance()->objList.at(j)->getType() == 1)
				{
					Rect* r1 = (Rect*)SceneManager::GetInstance()->objList.at(i);
					Rect* r2 = (Rect*)SceneManager::GetInstance()->objList.at(j);
					cout << r1->yPos << " " << r2->yPos << endl;
					if (r1->yPos + r1->height >= r2->yPos)
					{
						SceneManager::GetInstance()->objList.at(i)->canMove = true;
						SceneManager::GetInstance()->objList.at(j)->canMove = false;
					}
					else if(r2->yPos + r2->height >= r1->yPos) {
						SceneManager::GetInstance()->objList.at(i)->canMove = false;
						SceneManager::GetInstance()->objList.at(j)->canMove = true;
					}
				}
			}
		}
	}

	
}

void GameDraw(ESContext *esContext)
{
	// Draw scene then swap buffer to display to screen
	PaintObject();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void GameExit()
{
	// Cleanup memory here
}

int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext );

	esCreateWindow(&esContext, "Framework", (int)SCREEN_W, (int)SCREEN_H, ES_WINDOW_RGB);
	if (!InitGraphics((int)SCREEN_W, (int)SCREEN_H))
		return 0;

	esRegisterDrawFunc(&esContext, GameDraw);
	esRegisterKeyDownFunc(&esContext, KeyDown);
	esRegisterKeyUpFunc(&esContext, KeyUp);
	esRegisterUpdateFunc(&esContext, GameUpdate);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop(&esContext);
	GameExit();
}