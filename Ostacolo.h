#pragma once
#pragma warning(disable: 4996)


#include <iostream>


class Ostacolo
{
	private:
		double xInit;
		double yInit;
		double xFinish;
		double yFinish;
		double width;
		double heigth;
		double cx;
		double cy;
		std::string type; // hole, block, ...

	public:
		Ostacolo();
		Ostacolo(double xInit, double xFin, double yInit, double yFin, std::string type);
		double getXInit();
		double getXFin();
		double getYInit();
		double getYFin();
		double getCX();
		double getCY();
		bool operator == (const Ostacolo& ostacolo);
		bool operator > (const Ostacolo& ostacolo);
		bool operator < (const Ostacolo& ostacolo);
		int Compare(const Ostacolo&);
		std::string getType();
		~Ostacolo();

};

