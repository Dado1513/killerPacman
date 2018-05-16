#pragma once
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
		Ostacolo(double,double,double,double,double,std::string);
		bool operator == (const Ostacolo& ostacolo);
		bool operator > (const Ostacolo& ostacolo);
		bool operator < (const Ostacolo& ostacolo);
		int Compare(const Ostacolo&);
		~Ostacolo();
};

