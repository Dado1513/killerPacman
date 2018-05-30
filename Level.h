#pragma once
#include "CollisionSystem.h"

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
using namespace std;


class Level
{
private:
	double startPoint;
	double endPoint;
	double widthSingleLevel; // larghezza di ogni singolo livello 

	vector<Ostacolo> obstacleListA; // level A
	vector<Ostacolo> floorListA;

	vector<Ostacolo> obstacleListB; // level B
	vector<Ostacolo> floorListB;

	vector<Ostacolo> obstacleListC; // level C
	vector<Ostacolo> floorListC;



public:
	Level();
	~Level();
	
	void fillCollisionSystemA(CollisionSystem *CS);
	void fillCollisionSystemB(CollisionSystem *CS);
	void fillCollisionSystemC(CollisionSystem *CS);

	void makeLevelA(double start);
	void makeLevelB(double start);
	void makeLevelC(double start);

	
	vector<Ostacolo> getObstacleVectorA();
	vector<Ostacolo> getFloorVectorA();

	vector<Ostacolo> getObstacleVectorB();
	vector<Ostacolo> getFloorVectorB();
	
	vector<Ostacolo> getObstacleVectorC();
	vector<Ostacolo> getFloorVectorC();


	double getStartPoint();
	double getEndPoint();

};

