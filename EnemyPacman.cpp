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

}


EnemyPacman::~EnemyPacman() {

}

std::string EnemyPacman::getState() {
	return this->state;
}

double EnemyPacman::getLeft() {
	return posX - width;
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
		// ridotto la velocità per provenire tremolio del personaggio
		if (velX < 0.005) {
			velX = velX + 0.00015;
		}
	}
	else {
		//direzione sinistra
		state = "left";
		if (velX > 0) {
			velX = 0;
		}
		if (velX > -0.006) {
			velX = velX - 0.00015;
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
	if (std::strcmp(state.c_str(), "upLeft") != 0 && std::strcmp(state.c_str(), "upRight") != 0 && !isFalling) {
		//if (state != 3 && state != 2 && !isFalling){
		velY = 0.018;
		isFalling = true;

		if (std::strcmp(state.c_str(), "left") == 0 || std::strcmp(state.c_str(), "stopLeft") == 0) {
			state = "upLeft";
		}
		else {
			state = "upRight";
		}
	}

}
void EnemyPacman::stopY() {

	if (std::strcmp(state.c_str(), "upRight") == 0)
		state = "stopRight";
	if (std::strcmp(state.c_str(), "upLeft") == 0)
		state = "stopLeft";
	velY = 0;
	isFalling = false;
}



void EnemyPacman::update()
{
	//gestisco l'accelerazione decrescente del salto
	if (isFalling)
		velY -= 0.0003;

	posX += velX;
	posY += velY;

}