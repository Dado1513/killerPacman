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
		double length;
		std::string type; // hole, block, ...

	public:
		Ostacolo();
		Ostacolo(double xInit, double xFin, double yInit, double yFin, double length, std::string type);
		double getXInit();
		double getXFin();
		double getYInit();
		double getYFin();
		bool operator == (const Ostacolo& ostacolo);
		bool operator > (const Ostacolo& ostacolo);
		std::string getType();
		bool operator < (const Ostacolo& ostacolo);
		int Compare(const Ostacolo&);
		~Ostacolo();

};

