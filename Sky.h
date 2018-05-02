#pragma once
class Sky
{
	private:
		//posizione della nuvola
		double posX;
		double posY;

		//larghezza ed altezza della nuvola
		double width;
		double height;

		double vel;


	public:
		Sky(double posX, double posY, double width, double height);
		~Sky();
		void move(double vel, double limX, double respawn);
		double getLeft();
		double getRight();
		double getUp();
		double getDown();

};



	Sky::Sky(double posX, double posY, double width, double height)
	{
		this->posX = posX;
		this->posY = posY;

		this->width = width;
		this->height = height;

	}


	Sky::~Sky()
	{
	}

	void Sky::move(double velocity, double limX, double respawn) {
		vel = velocity;
		if (velocity == 0) {
			if (vel > 0)
				vel = vel - 0.00015;
			else
				vel = 0;
		}
			
		posX -= vel;

		if (posX+width < limX) {
			posX = respawn+width;
		}
	}

	double Sky::getLeft() {
		return posX - width;
	}

	double Sky::getRight() {
		return posX + width;
	}

	double Sky::getUp() {
		return posY + height;
	}

	double Sky::getDown() {
		return posY - height;
	}


