#include "LevelA.h"


//nel costruttore creo il livello di gioco
LevelA::LevelA()
{

	startPoint = 0.7;
	endPoint = 2.10;


	obstacleList.push_back(Ostacolo(0.7, 0.8, -0.4, -0.2, "obs") );
	obstacleList.push_back(Ostacolo(0.8, 0.9, -0.4, -0.2, "obs"));

	obstacleList.push_back(Ostacolo(0.95, 1.05, 0.1, 0.3, "obs"));
	obstacleList.push_back(Ostacolo(1.05, 1.15, 0.1, 0.3, "obs"));
	obstacleList.push_back(Ostacolo(1.15, 1.25, 0.1, 0.3, "obs"));

	obstacleList.push_back(Ostacolo(1.3, 1.4, -0.4, -0.2, "obs"));

	obstacleList.push_back(Ostacolo(1.75, 1.85, -0.1, 0.1, "obs"));
	obstacleList.push_back(Ostacolo(1.75, 1.85, -0.3, -0.1, "obs"));
	obstacleList.push_back(Ostacolo(1.75, 1.85, -0.5, -0.3, "obs"));
	obstacleList.push_back(Ostacolo(1.75, 1.85, -0.70, -0.50, "obs"));

	floorList.push_back(Ostacolo(1.75, 2.75, -1.0, -0.70, "Hole"));


}


//distruttore di default
LevelA::~LevelA() {}



void LevelA::fillCollisionSystem(CollisionSystem *CS) {
	for (vector<Ostacolo>::iterator it = obstacleList.begin(); it != obstacleList.end(); ++it) {
		CS->addObstacle( *it );
	}

	for (vector<Ostacolo>::iterator it = floorList.begin(); it != floorList.end(); ++it) {
		CS->addObstacle(*it);
	}

}


vector<Ostacolo> LevelA::getObstacleVector() {
	return this->obstacleList;
}

vector<Ostacolo> LevelA::getFloorVector() {
	return this->floorList;
}


double LevelA::getStartPoint() {
	return this->startPoint;
}

double LevelA::getEndPoint() {
	return this->endPoint;
}