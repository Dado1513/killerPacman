#pragma once
#include <iostream>
class EnemySimple{
	private:
		double posX;
		double posY;
		double width;
		double height;
		double velMaxX;
	public:
	EnemySimple(double posX, double posY, double width, double height);
	~EnemySimple();

	double getLeft();
	double getRight();
	double getUp();
	double getDown();
	double getX();
	double getY();

};

