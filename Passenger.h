#pragma once
#ifndef __Passenger__
#define __Passenger__
#include "../rt.h"

struct passengerData {
	int currFloor;
	int destFloor;
	bool isGoUp = false;
};

class Passenger : public ActiveClass {
private:
	passengerData* data;
public:
	Passenger();
	~Passenger();
	int getCurrFloor();
	int getDestFloor();
	bool getIsGoUp();
private:
	int main(void);
};
#endif // !__Passenger__
