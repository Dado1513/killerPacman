#pragma once
#include "Ostacolo.h"
#include "PC.h"

class CollisionSystem
{
private:
	std::vector<std::vector<Ostacolo>> array;
	double range;


public:
	CollisionSystem(double range);
	~CollisionSystem();
	void addObstacle(Ostacolo obs);
	void physics(PC* player);
	bool checkCollision(PC* player, Ostacolo *obstacle);
	bool isCollidingV1(double cx, double cy, double vertexX, double vertexY);
	bool isCollidingV2(double cx, double cy, double vertexX, double vertexY);

	int getIndex(double x);
	

	void read();
};

