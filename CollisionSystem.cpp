#include "CollisionSystem.h"
#include "Ostacolo.h"
#include "PC.h"
#include <cmath>

#include <windows.h>



int i;

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}


void CollisionSystem::addObstacle(Ostacolo* obs) {
	obstacle = obs;
}


void CollisionSystem::checkCollision(PC* player) {
	//controllo se il giocatore è in basso a sin, basso a dx, alto a sin, alto a dx rispetto all'ostacolo
	//NOTA: il player e l'ostacolo non si troveranno mai in situazioni degeneri di sovrapposizione (in assenza di bug..)

	


	double obsCX = obstacle->getCX();
	double obsCY = obstacle->getCY();

	

	double playerCX = player->getX();
	double playerCY = player->getY();

	double xDiff = obsCX - playerCX;
	double yDiff = obsCY - playerCY;

	double correctionX = 0.01;

	

	if (xDiff > 0 && yDiff > 0) {
		//player in basso a sinistra


		if (isCollidingV1(obstacle->getXInit(), obstacle->getYInit() + 5, player->getRight(), player->getUp() + 5)) {
		
			//controllo gli angoli per vedere se la collisione è in verticale (uno stop del salto) od orizzontale(stop corsa)
			if (abs(player->getRight() - correctionX  - obstacle->getXInit()) <= abs(player->getUp() - obstacle->getYInit())) {
				//stop corsa
				player->stopX();
				player->setX(player->getX() - 0.001);
			}else {
				player->obstacleY();
			}
		}

	}else {
	if (xDiff < 0 && yDiff > 0) {
		//player in basso a destra
		
		if (isCollidingV2(obstacle->getXFin(), obstacle->getYInit(), player->getLeft(), player->getUp())) {
			
			//controllo gli angoli per vedere se la collisione è in verticale (uno stop del salto) od orizzontale(stop corsa)
			if (abs(player->getLeft() - obstacle->getXFin()) <= abs(player->getUp() - obstacle->getYInit())) {
				//stop corsa
				player->stopX();
			}else {
				player->obstacleY();
			}
		}

	}else {
	if (xDiff > 0 && yDiff < 0) {

		//player in alto a sinistra
		if (isCollidingV2(player->getRight() - correctionX, player->getDown(), obstacle->getXInit(), obstacle->getYFin())) {

			if (abs(player->getRight() - obstacle->getXInit()) <= abs(player->getDown() - obstacle->getYFin())) {
				player->stopX();
				player->setX(player->getX() - 0.001);
			}else {
				player->stopY(obstacle->getYFin());
			}
		}

	}else {
		//player in alto a destra
		if (isCollidingV1(player->getLeft(), player->getDown(), obstacle->getXFin(), obstacle->getYFin())) {

			if (abs(player->getLeft() - obstacle->getXFin()) <= abs(player->getDown() - obstacle->getYFin())) {
				//stop corsa
				player->stopX();
			}else {
				player->stopY(obstacle->getYFin());
			}
		}
	}

	}
	}
}

/*
char out[100];
sprintf(out, " CollisionSystem");
i++;
OutputDebugString(out);
OutputDebugString("\n");
*/

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
