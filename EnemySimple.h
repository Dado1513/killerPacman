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
		std::string state;
		bool isDead;
		bool isDeading; // sta muorendo quindi sprite dead
		int deadingTexture;
		bool notDraw;

	public:
	EnemySimple(double posX, double posY, double width, double height);
	~EnemySimple();

	void setNotDraw(bool);
	bool getNotDraw();
	double getLeft();
	double getRight();
	double getUp();
	double getDown();
	double getVelX();
	void addVelX(std::string dir);
	std::string getState();
	double getX();
	double getY();
	void setDead(bool);
	bool getDead();
	void setX(double posX);
	void setY(double posY);
	void setVelMaxX(double);
	double getVelMaxX();
	void update();
	void setIsDeding(bool);
	bool getIsDeading();
	void setDeadingTexture(int);
	int getDeadingTexture();


};

