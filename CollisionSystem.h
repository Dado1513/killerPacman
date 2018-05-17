#pragma once
#include "Ostacolo.h"
#include "PC.h"

class CollisionSystem
{
private:
	Ostacolo *obstacle;		//nota: senza inizializzazione diretta VS mi genera errori 

public:
	CollisionSystem();
	~CollisionSystem();
	void addObstacle(Ostacolo *obs);
	void checkCollision(PC* player);
	bool isCollidingV1(double cx, double cy, double vertexX, double vertexY);
	bool isCollidingV2(double cx, double cy, double vertexX, double vertexY);
	

};

