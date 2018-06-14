#include "EnemySimple.h"



EnemySimple::EnemySimple(double posX, double posY, double width, double height){
	this->posX = posX;
	this->posY = posY;

	this->width = width;
	this->height = height;
	this->velX = 0;
	this->velMaxX = 0.00145;
	this->accMaxX = 0.00002;

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


EnemySimple::~EnemySimple()
{
}
