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
	endPoint = 30;
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
	
	if (startC == 20) {
		endC = endC + 3;
	}

	if (startA == 20) {
		endA = endA + 3;
	}

	if (startB == 20) {
		endB = endB + 3;
	}

	bool testing = true;
	if (testing) {
		startA = 0;
		endA = 10;
		startB = 10;
		endB = 20;
		startC = 20;
		endC = 33;
	}
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
	obstacleListA.push_back(Ostacolo(startA + 2.05, startA + 2.15, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.15, startA + 2.25, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 2.25, startA + 2.35, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.35, startA + 2.45, 0.1, 0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 2.45, startA + 2.55, 0.1, 0.3, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 2.6, startA + 2.7, -0.4, -0.2, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.1, 0.1, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.3, -0.1, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.5, -0.3, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 3.05, startA + 3.15, -0.70, -0.50, "obs"));
	
	floorListA.push_back(Ostacolo(startA + 3.05, startA +4.02, -1.0, -0.70, "Floor"));
	
	obstacleListA.push_back(Ostacolo(startA + 4.15, startA + 4.25, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.25, startA + 4.35, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.55, startA + 4.65, -0.2, 0.0, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 4.65, startA + 4.75, -0.2, 0.0, "obs"));

	obstacleListA.push_back(Ostacolo(startA + 4.85, startA + 4.95, -0.4, -0.2, "obs"));

	floorListA.push_back(Ostacolo(startA + 5.05, startA + 6.625, -1.0, -0.70, "Floor"));

	obstacleListA.push_back(Ostacolo(startA + 6.75, startA + 6.85, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.05, startA + 7.15, -0.4, -0.2, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.15, startA + 7.25, -0.4, -0.2, "obs"));
	
	floorListA.push_back(Ostacolo(startA + 7.45, startA + 8.12, -1.0, -0.70, "Floor"));
	obstacleListA.push_back(Ostacolo(startA + 7.75, startA + 7.85, -0.7, -0.5, "obs"));
	obstacleListA.push_back(Ostacolo(startA + 7.85, startA + 7.95, -0.7, -0.5, "obs"));
	//obstacleListA.push_back(Ostacolo(startA + 7.85, startA + 7.95, -0.5, -0.3, "obs"));


	floorListA.push_back(Ostacolo(startA + 8.35, endA, -1.0, -0.70, "Floor"));
	// HERE INSERT ENEMY 

}

void Level::makeLevelB() {

	// per adesso solo Floor
	floorListB.push_back(Ostacolo(startB , startB + 1.67 , -1.0, -0.70, "Floor"));
	// simple hole
	obstacleListB.push_back(Ostacolo(startB + 1.85, startB + 1.95, -0.4, -0.2, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 1.95, startB + 2.05, -0.4, -0.2, "obs"));

	floorListB.push_back(Ostacolo(startB + 2.15, startB + 3.75, -1.0, -0.70, "Floor"));

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
	obstacleListB.push_back(Ostacolo(startB + 7.65, startB + 7.75, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.75, startB + 7.85, -0.2, 0.0, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 7.85, startB + 7.95, -0.2, 0.0, "obs"));

	floorListB.push_back(Ostacolo(startB + 8.05, startB + 8.55, -1.0, -0.70, "Floor"));

	floorListB.push_back(Ostacolo(startB + 8.75, endB, -1.0, -0.70, "Floor"));

	obstacleListB.push_back(Ostacolo(startB + 8.95, startB + 9.05, -0.7, -0.5, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.05, startB + 9.15, -0.7, -0.5, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.35, startB + 9.45, -0.3, -0.1, "obs"));
	obstacleListB.push_back(Ostacolo(startB + 9.45, startB + 9.55, -0.3, -0.1, "obs"));


}


void Level::makeLevelC() {

	floorListC.push_back(Ostacolo(startC, startC + 1, -1.0, -0.70, "Floor"));

	obstacleListC.push_back(Ostacolo(startC + 1.15, startC + 1.25, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 1.25, startC + 1.35, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 1.55, startC + 1.65, -0.5, -0.3, "obs"));
	
	floorListC.push_back(Ostacolo(startC + 1.75, startC + 2, -1.0, -0.70, "Floor"));

	obstacleListC.push_back(Ostacolo(startC + 2.45, startC + 2.55, -0.7, -0.5, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 2.55, startC + 2.65, -0.7, -0.5, "obs"));
	floorListC.push_back(Ostacolo(startC + 2.2, startC + 3, -1.0, -0.7, "Floor"));
	
	obstacleListC.push_back(Ostacolo(startC + 3.07, startC + 3.15, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 3.15, startC + 3.25, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 3.35, startC + 3.45, -0.5, -0.3, "obs"));

	floorListC.push_back(Ostacolo(startC + 3.65, startC + 3.85, -1.0, -0.7, "Floor"));

	floorListC.push_back(Ostacolo(startC + 4.05, startC + 4.5, -1.0, -0.7, "Floor"));
	obstacleListC.push_back(Ostacolo(startC + 4.65, startC + 4.75, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 4.75, startC + 4.85, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 4.85, startC + 4.95, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 5.05, startC + 5.15, -0.7, -0.5, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 5.05, startC + 5.15, -0.5, -0.3, "obs"));
	floorListC.push_back(Ostacolo(startC + 5.05, startC + 5.55, -1.0, -0.7, "Floor"));

	obstacleListC.push_back(Ostacolo(startC + 5.65, startC + 5.75, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 5.75, startC + 5.85, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 5.95, startC + 6.05, -0.3, -0.1, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 6.05, startC + 6.15, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 6.25, startC + 6.35, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 6.35, startC + 6.45, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 6.55, startC + 6.65, -0.7, -0.5, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 6.85, startC + 6.95, -0.5, -0.3, "obs"));

	floorListC.push_back(Ostacolo(startC + 6.55, startC + 7.05, -1.0, -0.7, "Floor"));

	floorListC.push_back(Ostacolo(startC + 7.15, startC + 8.65, -1.0, -0.7, "Floor"));
	obstacleListC.push_back(Ostacolo(startC + 7.35, startC + 7.45, -0.7, -0.5, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 7.35, startC + 7.45, -0.5, -0.3, "obs"));

	obstacleListC.push_back(Ostacolo(startC + 7.75, startC + 7.85, -0.7, -0.5, "obs"));
	
	obstacleListC.push_back(Ostacolo(startC + 7.95, startC + 8.05, -0.7, -0.5, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 8.35, startC + 8.45, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 8.45, startC + 8.55, -0.5, -0.3, "obs"));
	
	obstacleListC.push_back(Ostacolo(startC + 8.75, startC + 8.85, -0.5, -0.3, "obs"));
	obstacleListC.push_back(Ostacolo(startC + 8.85, startC + 8.95, -0.5, -0.3, "obs"));

	floorListC.push_back(Ostacolo(startC + 9, startC + 9.55, -1.0, -0.7, "Floor"));

	floorListC.push_back(Ostacolo(startC + 9.85, endC, -1.0, -0.7, "Floor"));

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