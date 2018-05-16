# include <iostream>
# include <list>
# include "Ostacolo.h"
#pragma once
class Level{
	// classe per la gestione del livello 
	// il quale è una parte di gioco
	// nel gioco c'è ne saranno 3
	// che verranno mischiati randomicamnete all'inizio
	private:
		double xStart;
		double xFinish;
		std::list<Ostacolo> listaOstacoli;
	public:
		Level(double,double);
		void addOstacolo(Ostacolo);
		std::list<Ostacolo> getOstacoli();
		void makeLevel(int);
		~Level();

};

