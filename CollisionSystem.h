#pragma once
#include "Ostacolo.h"
#include "PC.h"
#include "EnemyPacman.h"
class CollisionSystem
{
private:
	std::vector<std::vector<Ostacolo>> array; // perchè vector di vector ? 
	double range;


public:
	CollisionSystem(double range);
	~CollisionSystem();
	void addObstacle(Ostacolo obs);
	void physics(EnemyPacman* pacman);
	void physics(PC* player);
	bool checkCollision(PC* player, Ostacolo *obstacle);
	bool checkCollision2(PC* player, Ostacolo *obstacle);
	bool checkCollision(EnemyPacman* pacman, Ostacolo *obstacle);
	bool checkCollision2(EnemyPacman* pacman, Ostacolo *obstacle);

	bool isCollidingV1(double cx, double cy, double vertexX, double vertexY);
	bool isCollidingV2(double cx, double cy, double vertexX, double vertexY);
	bool isHole(Ostacolo *ostacolo);
	bool collisionFloor(double, double);
	int getIndex(double x);
	

	void read();
};

