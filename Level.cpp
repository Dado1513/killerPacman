#include "Level.h"
# include <random>

//nel costruttore creo il livello di gioco
Level::Level()
{
	// creato le funzioni apposita per creare diversi livelli
	// la cosa bella sarebbe renderli causali con durata fissa
	// per esempio ogni livello è largo "30" ne mettiamo 3 nel gioco
	// da 0 a 90 e la creazione del livello è dipendente dall posizione start e end di esso
	// per esempio numero random tra 1 e 3 per il livello A a seconda del numero uscito si posizionerà nella
	// posizione prestabilita 1 o 2 o 3
	// stessa cosa per gli altri due andando ad esclusion naturalmente
	startPoint = 0.7; // numeri fittizi per adesso
	endPoint = 10;
	widthSingleLevel = 30; // larghezza di ogni singolo 
	this->makeLevelA(10,20); // parte da 10 da quando finisce il levelB
	this->makeLevelB(0.7,10); // parte da 0.7 da quando finisce il paviemnto

}


//distruttore di default
Level::~Level() {}

void Level::makeLevelA(double start, double end) {

	//start = 0.7;
	//endPoint = start + 1.4;

	// così basta cambiare lo start point per spostare il livello
	obstacleListA.push_back(Ostacolo(start + 0.0, start + 0.1, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(start + 0.1, start + 0.2, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(start + 0.25, start + 0.35, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(start + 0.35, start + 0.45, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(start + 0.45, start + 0.55, 0.1, 0.3, "obs"));

	obstacleListA.push_back(Ostacolo(start + 0.6, start + 0.7, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(start + 1.05, start + 1.15, -0.1, 0.1, "obs"));
	obstacleListA.push_back(Ostacolo(start + 1.05, start + 1.15, -0.3, -0.1, "obs"));
	obstacleListA.push_back(Ostacolo(start + 1.05, start + 1.15, -0.5, -0.3, "obs"));
	obstacleListA.push_back(Ostacolo(start + 1.05, start + 1.15, -0.70, -0.50, "obs"));
	
	// floor finale
	//floorListA.push_back(Ostacolo(start + 1.05, start + widthSingleLevel + 1.05, -1.0, -0.70, "Floor"));
	floorListA.push_back(Ostacolo(start + 1.05, end, -1.0, -0.70, "Floor"));

}

void Level::makeLevelB(double start, double end) {

	// per adesso solo Floor
	floorListB.push_back(Ostacolo(start , start + 3.67 , -1.0, -0.70, "Floor"));
	// simple hole
	obstacleListB.push_back(Ostacolo(start + 3.85, start + 3.95, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 3.95, start + 4.05, -0.4, -0.2, "obs"));
	// other floor
	floorListB.push_back(Ostacolo(start +4.2, start+5, -1.0, -0.70, "Floor"));

	obstacleListB.push_back(Ostacolo(start + 5.15, start + 5.25, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 5.25, start + 5.35, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 5.35, start + 5.45, -0.4, -0.2, "obs"));

	obstacleListB.push_back(Ostacolo(start + 5.75, start + 5.85, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 5.85, start + 5.95, -0.4, -0.2, "obs"));

	floorListB.push_back(Ostacolo(start + 6.2, start+7, -1.0, -0.70, "Floor"));


	obstacleListB.push_back(Ostacolo(start + 7.25, start + 7.35, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 7.35, start + 7.45, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 7.45, start + 7.55, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(start + 7.55, start + 7.65, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(start + 7.65, start + 7.75, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(start + 7.75, start + 7.85, -0.2, 0.0, "obs"));

	floorListB.push_back(Ostacolo(start + 8, end, -1.0, -0.70, "Floor"));

}

void Level::fillCollisionSystemA(CollisionSystem *CS) {
	for (vector<Ostacolo>::iterator it = obstacleListA.begin(); it != obstacleListA.end(); ++it) {
		CS->addObstacle( *it );
	}

	for (vector<Ostacolo>::iterator it = floorListA.begin(); it != floorListA.end(); ++it) {
		CS->addObstacle(*it);
	}

}
void Level::fillCollisionSystemB(CollisionSystem *CS) {
	for (vector<Ostacolo>::iterator it = obstacleListB.begin(); it != obstacleListB.end(); ++it) {
		CS->addObstacle(*it);
	}

	for (vector<Ostacolo>::iterator it = floorListB.begin(); it != floorListB.end(); ++it) {
		CS->addObstacle(*it);
	}

}

void Level::fillCollisionSystemC(CollisionSystem *CS) {
	for (vector<Ostacolo>::iterator it = obstacleListC.begin(); it != obstacleListC.end(); ++it) {
		CS->addObstacle(*it);
	}

	for (vector<Ostacolo>::iterator it = floorListC.begin(); it != floorListC.end(); ++it) {
		CS->addObstacle(*it);
	}

}

vector<Ostacolo> Level::getObstacleVectorA() {
	return this->obstacleListA;
}

vector<Ostacolo> Level::getFloorVectorA() {
	return this->floorListA;
}

vector<Ostacolo> Level::getObstacleVectorB() {
	return this->obstacleListB;
}

vector<Ostacolo> Level::getFloorVectorB() {
	return this->floorListB;
}
vector<Ostacolo> Level::getObstacleVectorC() {
	return this->obstacleListC;
}

vector<Ostacolo> Level::getFloorVectorC() {
	return this->floorListC;
}

double Level::getStartPoint() {
	return this->startPoint;
}

double Level::getEndPoint() {
	return this->endPoint;
}