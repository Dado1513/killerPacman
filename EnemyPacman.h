#pragma once
#include <iostream>
class EnemyPacman{
	//VARIABILI:
	private:

		//posizione del PC nella finestra
		double posX;
		double posY;

		//larghezza ed altezza del PC
		double width;
		double height;
		double velMaxX;

		//velocità corrente del PC
		double velX;		//corsa
		double velY;		//salto
		std::string state;			//stato del pg.
		bool isFalling;		//se il pg sta cadendo, non posso saltare.
		
		std::string direction;
		int timeFly;
		double accMaxX;
				/*
		direction = stopLeft == -1, stopRight==0, right==1, left==2, upRight==3, upLeft==4;
		*/

		//(evito che, se la velocitàY sia 0, si possa fare un doppio salto)
		/*
		nota: meglio cambiare gli stati in stringa, in modo che sia più immediato riconoscerli

		-1 -> fermo sinistra
		0 -> fermo destra

		1 -> movimento destra
		2 -> movimento sinistra
		3-> saltanto destra
		4-> saltando sinistra

		*/


	public:


		//METODI:
		EnemyPacman(double posX, double posY, double width, double height);
		~EnemyPacman();

		double getLeft();
		double getRight();
		double getUp();
		double getDown();
		double getX();
		double getY();
		std::string getState();
		void setX(double posX);
		void setY(double posY);
		void setVelMaxX(double);
		double getVelMaxX();
		//gestisco le velocità
		void addVelX(std::string dir);
		void stopX();
		void jump();
		void stopY();
		void obstacleY();

		void stopY(double);
		double getVelX();
		//aggiorno la posizione di mario
		void update();
		bool getFalling();

};

