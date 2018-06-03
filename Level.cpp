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
	
	startPoint = 00; // numeri fittizi per adesso
	endPoint = 20;
	widthSingleLevel = 10; // larghezza di ogni singolo 
	
	startA = rand() % 3 * 10; // 0 o 10 o 20
	endA = startA + widthSingleLevel;
	startB = rand()%3 * 10;
	
	while (startA == startB) {
		startB = rand() % 3 * 10;
	}
	endB = startB + widthSingleLevel;

	startC = 0; // di default 0
	if (startA + startB == 10) { // uno è 10 e uno è 0
		startC = 20;
	}
	else if (startA + startB == 20) { // uno è 20 e uno è 0
		startC = 10;
	}

	endC = startC + widthSingleLevel;
	
	this->makeLevelA(); 
	this->makeLevelB(); 
	this->makeLevelC(); 
}


//distruttore di default
Level::~Level() {}

void Level::makeLevelA() {

	//start = 0.7;
	//endPoint = start + 1.4;
	floorListA.push_back(Ostacolo(startA , startA + 2, -1.0, -0.70, "Floor"));

	// così basta cambiare lo start point per spostare il livello
	obstacleListA.push_back(Ostacolo(startA + 2.0, startA + 2.1, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.1, startA + 2.2, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 2.25, startA + 2.35, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.35, startA + 2.45, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.45, startA + 2.55, 0.1, 0.3, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 2.6, startA + 2.7, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.1, 0.1, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.3, -0.1, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.5, -0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.70, -0.50, "obs"));
	
	floorListA.push_back(Ostacolo(startA + 3.05, startA +4.05, -1.0, -0.70, "Floor"));
	
	obstacleListA.push_back(Ostacolo(startA + 4.15, startA + 4.25, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.25, startA + 4.35, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.35, startA + 4.45, -0.2, 0.0, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.45, startA + 4.55, -0.2, 0.0, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 4.75, startA + 4.85, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.85, startA + 4.95, -0.4, -0.2, "obs"));

	floorListA.push_back(Ostacolo(startA + 5.05, startA + 6.55, -1.0, -0.70, "Floor"));

	obstacleListA.push_back(Ostacolo(startA + 6.75, startA + 6.85, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.05, startA + 7.15, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.15, startA + 7.25, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 7.75, startA + 7.85, -0.7, -0.5, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.85, startA + 7.95, -0.7, -0.5, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.85, startA + 7.95, -0.5, -0.3, "obs"));

	floorListA.push_back(Ostacolo(startA + 7.45, startA + 8.05, -1.0, -0.70, "Floor"));

	floorListA.push_back(Ostacolo(startA + 8.25, endA, -1.0, -0.70, "Floor"));

}

void Level::makeLevelB() {

	// per adesso solo Floor
	floorListB.push_back(Ostacolo(startB , startB + 1.67 , -1.0, -0.70, "Floor"));
	// simple hole
	obstacleListB.push_back(Ostacolo(startB + 1.85, startB + 1.95, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 1.95, startB + 2.05, -0.4, -0.2, "obs"));

	floorListB.push_back(Ostacolo(startB + 2.15, startB + 3.67, -1.0, -0.70, "Floor"));

	obstacleListB.push_back(Ostacolo(startB + 3.85, startB + 3.95, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 3.95, startB + 4.05, -0.4, -0.2, "obs"));
	// other floor
	floorListB.push_back(Ostacolo(startB + 4.2, startB + 5, -1.0, -0.70, "Floor"));

	obstacleListB.push_back(Ostacolo(startB + 5.15, startB + 5.25, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 5.25, startB + 5.35, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 5.35, startB + 5.45, -0.4, -0.2, "obs"));

	obstacleListB.push_back(Ostacolo(startB + 5.75, startB + 5.85, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 5.85, startB + 5.95, -0.4, -0.2, "obs"));

	floorListB.push_back(Ostacolo(startB + 6.2, startB + 7, -1.0, -0.70, "Floor"));


	obstacleListB.push_back(Ostacolo(startB + 7.25, startB + 7.35, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.35, startB + 7.45, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.45, startB + 7.55, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.55, startB + 7.65, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.65, startB + 7.75, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.75, startB + 7.85, -0.2, 0.0, "obs"));

	floorListB.push_back(Ostacolo(startB + 8, startB + 8.5, -1.0, -0.70, "Floor"));

	obstacleListB.push_back(Ostacolo(startB + 8.95, startB + 9.05, -0.7, -0.5, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.05, startB + 9.15, -0.7, -0.5, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.35, startB + 9.45, -0.3, -0.1, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.45, startB + 9.55, -0.3, -0.1, "obs"));

	floorListB.push_back(Ostacolo(startB + 8.7, endB, -1.0, -0.70, "Floor"));

}

double Level::getStartA() {
	return this->startA;
}

double Level::getStartB() {
	return this->startB;
}

double Level::getStartC() {
	return this->startC;
}

double Level::getEndA() {
	return this->endA;
}

double Level::getEndB() {
	return this->endB;
}

double Level::getEndC() {
	return this->endC;
}


void Level::makeLevelC() {
	floorListC.push_back(Ostacolo(startC , endC, -1.0, -0.70, "Floor"));
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