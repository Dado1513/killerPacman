#include "Level.h"
#include <stdlib.h>     
#include <random>

Level::Level(double xStart, double xFinish){
	this->xStart = xStart;
	this->xFinish = xFinish;
}

void Level::makeLevel(int massimoOstacoli) {
	// creo ostacoli numero massimo per livello
	// type ostacolo
	std::string type[2];
	type[0] = "obs";
	type[1] = "hole";

	for (int i = 0; i < massimoOstacoli; i++) {
		// genero xOstacolo che deve compreso tra xStart e xFinish 
		int xOstacolo = rand() %(int(xFinish - xStart)) + xStart;
		// stessa cosa con type
		// se type block --> guardo anche a che altezza lo devo mettere
		// dopodichè li devo ordinare
		// call add ostacolo
	}
	// creare funzione che li compara
	//this->listaOstacoli.sort();
}
void Level::addOstacolo(Ostacolo o) {
	this->listaOstacoli.push_front(o);
}
std::list<Ostacolo> Level::getOstacoli() {
	return this->listaOstacoli;
}

Level::~Level()
{
}
