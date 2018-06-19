#include "PC.h"
#include <iostream>

PC::PC(double posX, double posY, double width, double height){
	
	this->posX = posX;
	this->posY = posY;

	this->width = width;
	this->height = height;

	this->velX = 0;
	this->velY = 0;
	this->state = "stopRight";
	this->isFalling = false;
	this->isInHole = false;
	this->dead = false;
	this->velMaxX = 0.0015;
	//this->velMaxX = 0.002;

	this->timeFly = 0;
	this->accMaxX = 0.00002;
}


PC::~PC(){

}

double PC::getWidth() {
	return this->width;
}
std::string PC::getState() {
	return this->state;
}
bool PC::getDead() {
	return this->dead;
}
void PC::setDead(bool dead) {
	this->dead = dead;
}
double PC::getLeft(){
	return posX - width;
}

double PC::getVelX() {
	return velX;
}

double PC::getRight(){
	return posX + width;
}

double PC::getUp()
{
	return posY + height;
}

double PC::getDown()
{
	return posY - height;
}

void PC::setX(double posX)
{
	this->posX = posX;
}

void PC::setY(double posY)
{
	this->posY = posY;
}

double PC::getX() 
{
	return this->posX;
}

double PC::getY()
{
	return this->posY;
}

bool PC::getIsInHole() {
	return this->isInHole;
}

void PC::setIsInHole(bool value) {
	this->isInHole = value;
}

double PC::getVelMaxX() {
	return velMaxX;
}

void PC::setVelMaxX(double velMaxX) {
	this->velMaxX = velMaxX;
}

void PC::addVelX(std::string dir)
{
	if (std::strcmp(dir.c_str(),"right")==0){
		//direzione destra
		state = "right";
		if (velX < 0) {
			velX = 0;
		}
		// ridotto la velocità per provenire tremolio del personaggio
		if (velX < velMaxX) {
			velX = velX + accMaxX;
		}
	} else if(std::strcmp(dir.c_str(), "left") == 0){
		//direzione sinistra
		state = "left";
		if (velX > 0) {
			velX = 0;
		}
		if (velX > -velMaxX) {
			velX = velX - accMaxX;
		}
	}
}

double PC::getVelY() {
	return this->velY;
}

void PC::stopX(){
	//se non sta saltando
	if (!getFalling() && std::strcmp(state.c_str(), "upLeft") != 0 || std::strcmp(state.c_str(), "upRight") != 0){
		//posizione vista
		if (std::strcmp(state.c_str(),"left") == 0)
			state = "stopLeft";
		if (std::strcmp(state.c_str(), "right") == 0)
			state = "stopRight";
	}
	
	velX = 0;
}

bool PC::getFalling() {
	return this->isFalling;
}


void PC::jump( audiere::OutputStreamPtr jump ){
	
	if(!isFalling){
		jump->play();
		velY = 0.006;
		isFalling = true;
		

		if (std::strcmp(state.c_str(), "left") == 0 || std::strcmp(state.c_str(), "stopLeft") == 0 ) {
			state = "upLeft";
		}
		else {
			state = "upRight";
		}
	}
		
}

void PC::stopY(double limY){

	isFalling = false;

	if (std::strcmp(state.c_str(), "upRight") == 0)
		state = "stopRight";
	if (std::strcmp(state.c_str(), "upLeft") == 0)
		state = "stopLeft";
	velY = 0;

	posY = limY + height;
	
}

void PC::obstacleY() {
	velY = -0.002;
}

void PC::update()
{
	//gestisco l'accelerazione decrescente del salto
	
	if (isFalling && timeFly > 11) {
		velY -= 0.0004;
		timeFly = 0;
	}
	else {
		timeFly = timeFly + 1;
	}
	
	posX += velX;
	posY += velY;

}


void PC::setFalling(bool fall) {
	isFalling = fall;
}