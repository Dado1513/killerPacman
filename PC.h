#pragma once
#include <iostream>
class PC
{
	//VARIABILI:
	private:
	
		//posizione del PC nella finestra
		double posX;
		double posY;
	
		//larghezza ed altezza del PC
		double width;
		double height;

		//velocit� corrente del PC
		double velX;		//corsa
		double velY;		//salto
		std::string state;			//stato del pg.
		bool isFalling;		//se il pg sta cadendo, non posso saltare.
		std::string direction;
		/*
			direction = stopLeft == -1, stopRight==0, right==1, left==2, upRight==3, upLeft==4;
		*/

							//(evito che, se la velocit�Y sia 0, si possa fare un doppio salto)
		/*
		nota: meglio cambiare gli stati in stringa, in modo che sia pi� immediato riconoscerli

		-1 -> fermo sinistra
		0 -> fermo destra

		1 -> movimento destra
		2 -> movimento sinistra
		3-> saltanto destra
		4-> saltando sinistra
		
		*/

		
	public:


		//METODI:
		PC(double posX, double posY, double width, double height);
		~PC();

		double getLeft();
		double getRight();
		double getUp();
		double getDown();
		double getX();
		double getY();
		std::string getState();
		void setX(double posX);
		void setY(double posY);

		//gestisco le velocit�
		void addVelX(std::string dir);
		void stopX();
		void jump();
		void stopY();
		double getVelX();
		//aggiorno la posizione di mario
		void update();
		bool getFalling();
};

