#include "PC.h"


PC::PC(double posX, double posY, double width, double height){
	
	this->posX = posX;
	this->posY = posY;

	this->width = width;
	this->height = height;

	this->velX = 0;
	this->velY = 0;
	this->state = 0;
	this->isFalling = false;

}


PC::~PC(){

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


void PC::addVelX(int dir)
{
	if (dir == 1){
		//direzione destra
		state = 1;
		if (velX < 0) {
			velX = 0;
		}
		// ridotto la velocità per provenire tremolio del personaggio
		if (velX < 0.003) {
			velX = velX + 0.00015;
			
		}
	} else{
		//direzione sinistra
		state = 2;
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
	if (state != 3 || state != 4){
		//posizione vista
		if (state == 2)
			state = -1;
		if (state == 1)
			state = 0;
	}
	
	velX = 0;
}

void PC::jump(){
	//se non sta saltando, compio il salto
	if (state != 3 && state != 2 && !isFalling){
		velY = 0.018;
		isFalling = true;
	}
		
}
void PC::stopY(){
	if (state == 3)
		state = 0;
	if (state == 4)
		state = -1;
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