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

}


PC::~PC(){

}

std::string PC::getState() {
	return this->state;
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


void PC::addVelX(std::string dir)
{
	if (std::strcmp(dir.c_str(),"right")==0){
		//direzione destra
		state = "right";
		if (velX < 0) {
			velX = 0;
		}
		// ridotto la velocità per provenire tremolio del personaggio
		if (velX < 0.003) {
			velX = velX + 0.00015;
			
		}
	} else{
		//direzione sinistra
		state = "left";
		if (velX > 0) {
			velX = 0;
		}
		if (velX > -0.003) {
			velX = velX - 0.00015;
		}
	}
}
void PC::stopX()
{
	//se non sta saltando
	if (std::strcmp(state.c_str(), "upLeft") != 0 || std::strcmp(state.c_str(), "upRight") != 0){
		//posizione vista
		if (std::strcmp(state.c_str(),"left") == 0)
			state = "stopLeft";
		if (std::strcmp(state.c_str(), "right") == 0)
			state = "stopRight";
	}
	
	velX = 0;
}

void PC::jump(){
	//se non sta saltando, compio il salto
	// no dovrebbe essere 3 e 4 invece che 3 e 2?
	if(std::strcmp(state.c_str(),"upLeft") !=0  && std::strcmp(state.c_str(), "upRight") != 0 && !isFalling){
	//if (state != 3 && state != 2 && !isFalling){
		velY = 0.018;
		isFalling = true;
	}
		
}
void PC::stopY(){

	if (std::strcmp(state.c_str(), "upRight") == 0)
		state = "stopRight";
	if (std::strcmp(state.c_str(), "upLeft") == 0)
		state = "stopLeft";
	velY = 0;
	isFalling = false;
}



void PC::update()
{
	//gestisco l'accelerazione decrescente del salto
	if (isFalling)
		velY -= 0.0003;

	posX += velX;
	posY += velY;

}