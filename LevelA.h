#pragma once
#include "CollisionSystem.h"

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
using namespace std;


class LevelA
{
private:
	double startPoint;
	double endPoint;

	vector<Ostacolo> obstacleList;
	vector<Ostacolo> floorList;


public:
	LevelA();
	~LevelA();

	void fillCollisionSystem(CollisionSystem *CS);
	vector<Ostacolo> getObstacleVector();
	vector<Ostacolo> getFloorVector();

	double getStartPoint();
	double getEndPoint();

};

