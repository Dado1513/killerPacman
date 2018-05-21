#include "CollisionSystem.h"
#include "Ostacolo.h"
#include "PC.h"
#include <cmath>
#include <sstream>


#include <windows.h>



int i;

CollisionSystem::CollisionSystem(double range)
{
	this->range = range;
}


CollisionSystem::~CollisionSystem()
{
}


void CollisionSystem::addObstacle(Ostacolo obs) {
	double posX = obs.getCX();
	double limX1 = obs.getXInit();
	double limX2 = obs.getXFin();




	//aggiungo l'ostacolo nella relativa posizione
	if (array.size() < getIndex(posX) + 1)
		array.resize(getIndex(posX) + 1);
	array[getIndex(posX)].push_back(obs);


	//se il blocco è piu grande dell'intervallo considerato, lo aggiungo anche negli slot successivi
	for (int i = getIndex(posX) + 1; i <= getIndex(limX2); i++) {
		
			if (array.size() < getIndex(limX2) + 1)
				array.resize(getIndex(limX2) + 1);
			array[i].push_back(obs);
	}

	//lo stesso per gli intervalli precedenti
	for (int i = getIndex(posX) - 1; i >= getIndex(limX1); i--) {
			array[i].push_back(obs);
	}

}

void CollisionSystem::read() {

	OutputDebugString("Leggo gli elementi presenti nel vettore:");
	OutputDebugString("\n");

	for (int l = 0; l < array.size(); l++) {
		char out[100];
		sprintf(out, " %d", array[l].size());
		OutputDebugString(out);
		OutputDebugString("\n");
	}
}


int CollisionSystem::getIndex(double x) {
	int multiplier = (int) (1 / range);

	int index = int(x * multiplier) + 1;
	if (index >= 0)
		return index;
	else
		return 0;
}


void CollisionSystem::physics(PC* player) {

	//se vera, il player non deve precipitare
	// TODO aggiungere il controllo se l'ostacolo è un buco e quindi il player deve precipitare
	boolean isInGround = false;
	boolean fall = false;
	//ottengo la posizione x del giocatore e dei suoi estremi.
	double posXc = player->getX();
	double posXl = player->getLeft();
	double posXr = player->getRight();

	//se non ci sono oggetti istanziati oltre la posizione di mario --> bug ( ci deve essere almeno il suolo )
	if (getIndex(posXr) >= array.size()) {
		player->setFalling(true);
		return;
	}
		

	// con OR ne basta uno vero e non precipita
	// invece se sono in un buco ne dovrebbe essere tutti veri
	// e ne basta uno falso che cado
	//controllo il quadrante dove è centrato il player
	if (array[getIndex(posXc)].size() != 0) {
		for (std::vector<Ostacolo>::iterator it = array[getIndex(posXc)].begin(); it != array[getIndex(posXc)].end(); ++it) {
			isInGround = isInGround || checkCollision(player, &(*it));		//brividi..

		}
	}
	
	//se il player supera il quadrante, devo verificare anche il successivo (o il precedente)
	if (getIndex(posXc) != getIndex(posXl) && !array[getIndex(posXl)].empty()) {
		for (std::vector<Ostacolo>::iterator it = array[getIndex(posXl)].begin(); it != array[getIndex(posXl)].end(); ++it) {
			isInGround = isInGround || checkCollision(player, &(*it));
		}
	}
	
	if (getIndex(posXc) != getIndex(posXr) && !array[getIndex(posXr)].empty()) {
		for (std::vector<Ostacolo>::iterator it = array[getIndex(posXr)].begin(); it != array[getIndex(posXr)].end(); ++it) {
			isInGround = isInGround || checkCollision(player, &(*it));
		}
	}
		
	
	//setto se mario sta cadendo o meno
	player->setFalling(!isInGround);
	

}
bool CollisionSystem::isHole(Ostacolo *ostacolo) {
	return std::strcmp(ostacolo->getType().c_str(), "Hole")== 0;
}
bool CollisionSystem::checkCollision(PC* player, Ostacolo *obstacle) {
	
	//controllo se il giocatore è in basso a sin, basso a dx, alto a sin, alto a dx rispetto all'ostacolo
	//NOTA: il player e l'ostacolo non si troveranno mai in situazioni degeneri di sovrapposizione (in assenza di bug..)
	// se l'ostacolo è un buco ?
	double obsCX = obstacle->getCX();
	double obsCY = obstacle->getCY();

	

	double playerCX = player->getX();
	double playerCY = player->getY();
	// NB se pavimento lungo 10 per esempio, quando mario supera il 5 in x non salta più
	// perchè dice che dovrebbe collidere in basso a sinistra ma non funziona
	double xDiff = obsCX - playerCX;
	double yDiff = obsCY - playerCY;

	double correctionX = 0.01;

	bool ground = false;

	if (isHole(obstacle)) {
		if (obstacle->getXInit() -correctionX <= player->getLeft() && player->getRight() <= obstacle->getXFin() + correctionX) {
			//OutputDebugString("Is in Hole");
			player->setIsInHole(true);
		}
		else {
			player->setIsInHole(false);
		}

	}
	else {

		if (xDiff > 0 && yDiff > 0) {
			//player e ostacolo in basso a sinistra
			// check this per non far scivolare l'omino
			//if (isCollidingV1(obstacle->getXInit(), obstacle->getYInit() + 5, player->getRight(), player->getUp() + 5)) {
			if (isCollidingV1(obstacle->getXInit(), obstacle->getYInit() , player->getRight(), player->getUp() )) {

			//controllo gli angoli per vedere se la collisione è in verticale (uno stop del salto) od orizzontale(stop corsa)
				if (abs(player->getRight() - correctionX - obstacle->getXInit()) <= abs(player->getUp() - obstacle->getYInit())) {
					//stop corsa
					player->stopX();
					player->setX(player->getX() - 0.001);
				}
				else {
					player->obstacleY();

				}
			}

		}
		else {
			if (xDiff < 0 && yDiff > 0) {
				//player e ostacolo in basso a destra

				if (isCollidingV2(obstacle->getXFin(), obstacle->getYInit(), player->getLeft(), player->getUp())) {
					//controllo gli angoli per vedere se la collisione è in verticale (uno stop del salto) od orizzontale(stop corsa)
					if (abs(player->getLeft() - obstacle->getXFin()) <= abs(player->getUp() - obstacle->getYInit())) {
						//stop corsa
						player->stopX();
					}
					else {
						player->obstacleY();
					}
				}

			}
			else {
				if (xDiff > 0 && yDiff < 0 ) {

					//player e ostacolo in alto a sinistra
					if (isCollidingV2(player->getRight() - correctionX, player->getDown(), obstacle->getXInit(), obstacle->getYFin())) {
						if (abs(player->getRight() - obstacle->getXInit()) <= abs(player->getDown() - obstacle->getYFin())) {
							player->stopX();
							player->setX(player->getX() - 0.001);
						}
						else {
							if (player->getX() >= obstacle->getXInit())
								player->stopY(obstacle->getYFin());

							ground = true;
						}
					}

				}
				else {
					//player e ostacolo in alto a destra
					if (std::strcmp(obstacle->getType().c_str(), "Floor") == 0) {
						if (isCollidingV2(player->getRight() - correctionX, player->getDown(), obstacle->getXInit(), obstacle->getYFin())) {
							if (abs(player->getRight() - obstacle->getXInit()) <= abs(player->getDown() - obstacle->getYFin())) {
								player->stopX();
								player->setX(player->getX() - 0.001);
							}
							else {
								if (player->getX() <= obstacle->getXFin())
									player->stopY(obstacle->getYFin());

								ground = true;
							}
						}
					}else 
						if (isCollidingV1(player->getLeft() , player->getDown(), obstacle->getXFin(), obstacle->getYFin())) {
						//	if (isCollidingV1(player->getLeft(), obstacle->getYFin(), obstacle->getXFin() , player->getDown())) {

						if (abs(player->getLeft() - obstacle->getXFin()) <= abs(player->getDown() - obstacle->getYFin())) {
							//stop corsa
							player->stopX();
							player->setX(player->getX() + 0.001);

						}
						else {
							if(player->getX() <= obstacle->getXFin())
								player->stopY(obstacle->getYFin());

							ground = true;
						}
					}
				}

			}
		}
	}
	
	//ritorno true se il player ha una base stabile senza precipitare
	return ground;
}

/*
char out[100];
sprintf(out, " CollisionSystem");
i++;
OutputDebugString(out);
OutputDebugString("\n");
*/

bool CollisionSystem::collisionFloor(double cy, double vertexY) {
	return cy > vertexY;
}
bool CollisionSystem::isCollidingV1(double cx, double cy, double vertexX, double vertexY) {
	if (cx < vertexX && cy < vertexY)
		return true;
	else
		return false;
}

bool CollisionSystem::isCollidingV2(double cx, double cy, double vertexX, double vertexY) {
	
	if (cx >= vertexX && cy <= vertexY)
		return true;
	else
		return false;

}
