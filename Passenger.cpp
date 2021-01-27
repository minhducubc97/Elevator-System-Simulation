#include <stdio.h>
#include <stdlib.h>
#include "Passenger.h"

CMutex* elevatorLineUp;
CTypedPipe<passengerData> p2i("ToIOPipe", 1024);

Passenger::Passenger() {
	data->currFloor = rand() % 10;
	data->destFloor = rand() % 10;
	while (data->destFloor == data->currFloor) {
		data->destFloor = rand() % 10;
	}
	if (data->destFloor > data->currFloor) {
		data->isGoUp = true;
	}
	else {
		data->isGoUp = false;
	}
}

Passenger::~Passenger() {
	delete elevatorLineUp;
}

int Passenger::getCurrFloor(){
	return data->currFloor;
}

int Passenger::getDestFloor(){
	return data->destFloor;
}

bool Passenger::getIsGoUp() {
	return data->isGoUp;
}

int Passenger::main(void) {
	elevatorLineUp->Wait();
	p2i.Write(data);
	elevatorLineUp->Signal();
	return 0;
}