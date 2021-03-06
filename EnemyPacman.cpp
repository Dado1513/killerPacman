#include "EnemyPacman.h"
#include <iostream>

EnemyPacman::EnemyPacman(double posX, double posY, double width, double height) {

	this->posX = posX;
	this->posY = posY;

	this->width = width;
	this->height = height;

	this->velX = 0;
	this->velY = 0;
	this->state = "stopRight";
	this->isFalling = false;
	this->velMaxX = 0.00145;
	//this->velMaxX = 0.00195;
	this->timeFly = 0;
	this->accMaxX = 0.00002;

}


EnemyPacman::~EnemyPacman() {

}

std::string EnemyPacman::getState() {
	return this->state;
}

double EnemyPacman::getLeft() {
	return posX - width;
}

double EnemyPacman::getVelMaxX() {
	return this->velMaxX;
}

void EnemyPacman::setVelMaxX(double velMaxX) {
	this->velMaxX = velMaxX;
}

double EnemyPacman::getVelX() {
	return velX;
}

double EnemyPacman::getRight() {
	return posX + width;
}

double EnemyPacman::getUp()
{
	return posY + height;
}

double EnemyPacman::getDown()
{
	return posY - height;
}

void EnemyPacman::setX(double posX)
{
	this->posX = posX;
}

void EnemyPacman::setY(double posY)
{
	this->posY = posY;
}

double EnemyPacman::getX()
{
	return this->posX;
}

double EnemyPacman::getY()
{
	return this->posY;
}


void EnemyPacman::addVelX(std::string dir)
{
	if (std::strcmp(dir.c_str(), "right") == 0) {
		//direzione destra
		state = "right";
		if (velX < 0) {
			velX = 0;
		}
		// ridotto la velocit� per provenire tremolio del personaggio
		if (velX < this->velMaxX) {
			velX = velX + accMaxX;
		}
	}
	else {
		//direzione sinistra
		state = "left";
		if (velX > 0) {
			velX = 0;
		}
		if (velX > -this->velMaxX) {
			velX = velX - accMaxX;
		}
	}
}
void EnemyPacman::stopX()
{
	//se non sta saltando
	if (std::strcmp(state.c_str(), "upLeft") != 0 || std::strcmp(state.c_str(), "upRight") != 0) {
		//posizione vista
		if (std::strcmp(state.c_str(), "left") == 0)
			state = "stopLeft";
		if (std::strcmp(state.c_str(), "right") == 0)
			state = "stopRight";
	}

	velX = 0;
}

bool EnemyPacman::getFalling() {
	return this->isFalling;
}
void EnemyPacman::jump() {
	
	//se non sta saltando, compio il salto
	// no dovrebbe essere 3 e 4 invece che 3 e 2?
	if (!isFalling) {
		//velY = 0.018;
		velY = 0.006;
		isFalling = true;

		if (std::strcmp(state.c_str(), "left") == 0 || std::strcmp(state.c_str(), "stopLeft") == 0) {
			state = "upLeft";
		}
		else {
			state = "upRight";
		}
	}

}
// add stopY --> similar PC
void EnemyPacman::stopY() {

	if (std::strcmp(state.c_str(), "upRight") == 0)
		state = "stopRight";
	if (std::strcmp(state.c_str(), "upLeft") == 0)
		state = "stopLeft";
	velY = 0;
	isFalling = false;
}

void EnemyPacman::stopY(double limY) {

		isFalling = false;

		if (std::strcmp(state.c_str(), "upRight") == 0)
			state = "stopRight";
		if (std::strcmp(state.c_str(), "upLeft") == 0)
			state = "stopLeft";
		velY = 0;

		posY = limY + height;

}

void EnemyPacman::obstacleY() {
	velY = -0.002;
}

void EnemyPacman::update()
{
	//gestisco l'accelerazione decrescente del salto
	if (isFalling && timeFly > 11) {
		velY -= 0.0004;
		timeFly = 0;
	}else {
		timeFly++;
	}

	posX += velX;
	posY += velY;

}
