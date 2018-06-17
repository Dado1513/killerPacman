#include "EnemySimple.h"



EnemySimple::EnemySimple(double posX, double posY, double width, double height){
	this->posX = posX;
	this->posY = posY;

	this->width = width;
	this->height = height;
	this->velX = 0;
	this->velMaxX = 0.01;
	this->accMaxX = 0.0002;
	this->state = "stopRight";
	this->isDead = false;

}

std::string EnemySimple::getState() {
	return this->state;
}

double EnemySimple::getLeft() {
	return posX - width;
}

double EnemySimple::getVelMaxX() {
	return this->velMaxX;
}

void EnemySimple::setVelMaxX(double velMaxX) {
	this->velMaxX = velMaxX;
}

double EnemySimple::getVelX() {
	return velX;
}

double EnemySimple::getRight() {
	return posX + width;
}

double EnemySimple::getUp()
{
	return posY + height;
}

double EnemySimple::getDown()
{
	return posY - height;
}

void EnemySimple::setX(double posX)
{
	this->posX = posX;
}

void EnemySimple::setY(double posY)
{
	this->posY = posY;
}

double EnemySimple::getX()
{
	return this->posX;
}

double EnemySimple::getY()
{
	return this->posY;
}


void EnemySimple::addVelX(std::string dir)
{
	if (std::strcmp(dir.c_str(), "right") == 0) {
		//direzione destra
		state = "right";
		if (velX < 0) {
			velX = 0;
		}
		// ridotto la velocità per provenire tremolio del personaggio
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

void EnemySimple::update() {
	posX += velX;
}
void EnemySimple::setDead(bool dead) {
	this->isDead = dead;
}

bool EnemySimple::getDead() {
	return this->isDead;
}

EnemySimple::~EnemySimple()
{
}
