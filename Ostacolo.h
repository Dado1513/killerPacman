#pragma once
#include <iostream>

class Ostacolo
{
	private:
		double xInit;
		double yInit;
		double xFinish;
		double yFinish;
		std::string type; // hole, block, ...

	public:
		Ostacolo();
		~Ostacolo();
};

