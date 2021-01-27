#pragma once
#ifndef __ELEVATOR__
#define __ELEVATOR__
#include "rt.h"

enum DoorStatus { CLOSED, OPEN };
enum Direction { UP, DOWN, STATIC };

int END_GAME = 0;
int E1_ERROR = 1;
int E2_ERROR = 2;
int E1_FIXED = 3;
int E2_FIXED = 4;
int UPSTAIR_REQUEST = 90;
int DOWNSTAIR_REQUEST = 10;
int SEQ_UPSTAIR_REQUEST = 900;
int SEQ_DOWNSTAIR_REQUEST = 100;

struct elevatorData {
	bool active;
	int currFloor;
	Direction direction;
	bool destFloors[10];
	DoorStatus door;
	int lights[10];
	bool maintenance;
};

CSemaphore p1("P1", 0, 1);
CSemaphore c1("C1", 1, 1);
CSemaphore p2("P2", 0, 1);
CSemaphore c2("C2", 1, 1);
CSemaphore p3("P3", 0, 1);
CSemaphore c3("C3", 1, 1);
CSemaphore p4("P4", 0, 1);
CSemaphore c4("C4", 1, 1);

CDataPool dp1("Elevator1", sizeof(struct elevatorData));
struct elevatorData *pointerToE1 = (struct elevatorData*)(dp1.LinkDataPool());
CDataPool dp2("Elevator2", sizeof(struct elevatorData));
struct elevatorData *pointerToE2 = (struct elevatorData*)(dp2.LinkDataPool());

class ElevatorStatus {
private:
	elevatorData elevatorGData = {
		false,
		0,
		STATIC,
		{false, false, false, false, false, false, false, false, false, false},
		CLOSED,
		{false, false, false, false, false, false, false, false, false, false},
	};
public:	
	elevatorData DispatcherGetElevator1Status() {
		if (p2.Read() > 0) {
			p2.Wait();
			elevatorGData = *pointerToE1;
			c2.Signal();
		}
		return elevatorGData;
	}

	elevatorData IOGetElevator1Status() {
		if (p1.Read() > 0) {
			p1.Wait();
			elevatorGData = *pointerToE1;
			c1.Signal();
		}
		return elevatorGData;
	}

	elevatorData DispatcherGetElevator2Status() {
		if (p4.Read() > 0) {
			p4.Wait();
			elevatorGData = *pointerToE2;
			c4.Signal();
		}
		return elevatorGData;
	}

	elevatorData IOGetElevator2Status() {
		if (p3.Read() > 0) {
			p3.Wait();
			elevatorGData = *pointerToE2;
			c3.Signal();
		}
		return elevatorGData;
	}

	void UpdateElevator1Status(elevatorData elevator) {
		c1.Wait();
		c2.Wait();
		*pointerToE1 = elevator;
		p1.Signal();
		p2.Signal();
	}

	void UpdateElevator2Status(elevatorData elevator) {
		c3.Wait();
		c4.Wait();
		*pointerToE2 = elevator;
		p3.Signal();
		p4.Signal();
	}
};

#endif // !__ELEVATOR__
