#pragma once
#include <iostream>
class EnemySimple{
	private:
		double posX;
		double posY;
		double width;
		double height;
		double velMaxX;
		double velX;		
		double accMaxX;

	public:
	EnemySimple(double posX, double posY, double width, double height);
	~EnemySimple();

	double getLeft();
	double getRight();
	double getUp();
	double getDown();
	double getVelX();

	double getX();
	double getY();
	void setX(double posX);
	void setY(double posY);
	void setVelMaxX(double);
	double getVelMaxX();


};

