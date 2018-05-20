#include "Ostacolo.h"
#include <iostream>

#include <iostream>


Ostacolo::Ostacolo(double xInit, double xFinish, double yInit, double yFinish, std::string type) {
	this->xInit = xInit;
	this->xFinish = xFinish;
	this->yInit = yInit;
	this->yFinish = yFinish;
	this->type = type;
	this->width = xFinish - xInit;
	this->heigth = yFinish - yInit;
	this->cx = xInit + width / 2;
	this->cy = yInit + heigth / 2;
}

int Ostacolo::Compare(const Ostacolo& ostacolo) {

	if (this->xInit < ostacolo.xInit && this->xFinish < ostacolo.xFinish) {
		return -1;
	}
	else if (this->xInit > ostacolo.xInit && this->xFinish > ostacolo.xFinish) {
		return 1;
	}
	else if (this->xInit < ostacolo.xInit) {
		return -1;
	}
	else if (this->xInit > ostacolo.xInit) {
		return 1;
	}
	else {
		return 0;
	}
}


// to check
bool Ostacolo::operator==(const Ostacolo& ostacolo) {
	return !Compare(ostacolo) &&
		std::strcmp(this->type.c_str(), ostacolo.type.c_str()) == 0;
}

bool Ostacolo::operator<(const Ostacolo& ostacolo) {
	return Compare(ostacolo)<0;
}
bool Ostacolo::operator>(const Ostacolo& ostacolo) {
	return Compare(ostacolo)>0;
}

Ostacolo::~Ostacolo()
{
}

double Ostacolo::getXInit() {
	return xInit;
}
double Ostacolo::getXFin() {
	return xFinish;
}
double Ostacolo::getYInit() {
	return yInit;
}
double Ostacolo::getYFin() {
	return yFinish;
}
double Ostacolo::getCX() {
	return cx;
}
double Ostacolo::getCY() {
	return cy;
}

std::string Ostacolo::getType() {
	return type;
}



