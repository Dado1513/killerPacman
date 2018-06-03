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
	double startA, startB, startC;
	double endA, endB, endC;
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

	void makeLevelA();
	void makeLevelB();
	void makeLevelC();


	
	vector<Ostacolo> getObstacleVectorA();
	vector<Ostacolo> getFloorVectorA();

	vector<Ostacolo> getObstacleVectorB();
	vector<Ostacolo> getFloorVectorB();
	
	vector<Ostacolo> getObstacleVectorC();
	vector<Ostacolo> getFloorVectorC();


	double getStartPoint();
	double getEndPoint();
	double getStartA();
	double getStartB();
	double getStartC();
	double getEndA();
	double getEndB();
	double getEndC();


};

