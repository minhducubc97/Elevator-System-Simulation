#include <stdio.h>
#include <stdlib.h>
#include "../Elevator.h"
#include "Passenger.h"

elevatorData elevator1Data;
elevatorData elevator2Data;	
CRendezvous startProgram("StartProgram", 4);
CTypedPipe<int> i2d("IOToDispatcherPipe", 1024);
ElevatorStatus e1Status;
ElevatorStatus e2Status;
bool inProgress;

UINT __stdcall toElevator1(void *args) {
	while (inProgress) {
		elevator1Data = e1Status.DispatcherGetElevator1Status();
	}
	return 0;
}

UINT __stdcall toElevator2(void *args) {
	while (inProgress) {
		elevator2Data = e2Status.DispatcherGetElevator2Status();
	}
	return 0;
}

int main(void) {
	inProgress = true;
	int pipeData = 0;
	bool isE1Functional = true;
	bool isE2Functional = true;
	int floor = 0;
	int factor = 0;
	int nextFloor = 0;
	int floorDiffE1 = 10;
	int floorDiffE2 = 10;
	bool isInAutoMode = false;

	cout << "Welcome to The Elevator!" << endl;

	CProcess io("D:\\Documents\\W-O-R-K\\CPEN 333\\Assignments\\Assignment 1\\Assignment1\\Debug\\IO.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);
	CProcess e1("D:\\Documents\\W-O-R-K\\CPEN 333\\Assignments\\Assignment 1\\Assignment1\\Debug\\Elevator1.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);
	CProcess e2("D:\\Documents\\W-O-R-K\\CPEN 333\\Assignments\\Assignment 1\\Assignment1\\Debug\\Elevator2.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);

	cout << "Press any key to start The Elevator program..." << endl;
	while (TEST_FOR_KEYBOARD() == 0) {}

	startProgram.Wait();

	CThread toE1(toElevator1, ACTIVE, NULL);
	CThread toE2(toElevator2, ACTIVE, NULL);

	while (inProgress) {
		if (i2d.TestForData() >= 0) {
			i2d.Read(&pipeData);
			if (pipeData == END_GAME) {
				inProgress = false;
				e1.Post(END_GAME);
				e2.Post(END_GAME);
				io.Post(END_GAME);
				break;
			}
			else if (pipeData == E1_ERROR) {
				if (isE1Functional) {
					isE1Functional = false;
					e1.Post(pipeData);
				}
			}
			else if (pipeData == E2_ERROR) {
				if (isE2Functional) {
					isE2Functional = false;
					e2.Post(pipeData);
				}
			}
			else if (pipeData == E1_FIXED) {
				if (!isE1Functional) {
					isE1Functional = true;
					e1.Post(pipeData);
				}
			}
			else if (pipeData == E2_FIXED) {
				if (!isE2Functional) {
					isE2Functional = true;
					e2.Post(pipeData);
				}
			}
			else {
				if (pipeData < 1000) {
					floor = pipeData % 10;			// last digit contains the floor number
					factor = pipeData / 10;
					isInAutoMode = false;
				}
				else {
					floor = pipeData % 10;
					nextFloor = (pipeData / 10) % 10;
					factor = (pipeData / 100);
					isInAutoMode = true;
				}

				if (factor == 1) {
					e1.Post(pipeData);
				}
				else if (factor == 2) {
					e2.Post(pipeData);
				}
				else {
					if (!isE1Functional) {
						floorDiffE1 = 10;
					}
					else {
						if (!elevator1Data.active) {
							floorDiffE1 = abs(floor - elevator1Data.currFloor);
						}
						else {
							if ((elevator1Data.direction == UP && factor == UPSTAIR_REQUEST && floor > elevator1Data.currFloor)
								||
								(elevator1Data.direction == DOWN && factor == DOWNSTAIR_REQUEST && floor < elevator1Data.currFloor)) {
								floorDiffE1 = abs(floor - elevator1Data.currFloor);
							}
							else {
								floorDiffE1 = 10;
							}
						}
					}

					if (!isE2Functional) {
						floorDiffE2 = 10;
					}
					else {
						if (!elevator2Data.active) {
							floorDiffE2 = abs(floor - elevator2Data.currFloor);
						}
						else {
							if ((elevator2Data.direction == UP && factor == UPSTAIR_REQUEST && floor > elevator2Data.currFloor)
								||
								(elevator2Data.direction == DOWN && factor == DOWNSTAIR_REQUEST && floor < elevator2Data.currFloor)) {
								floorDiffE2 = abs(floor - elevator2Data.currFloor);
							}
							else {
								floorDiffE2 = 10;
							}
						}
					}

					if (floorDiffE1 != 10 || floorDiffE2 != 10) {
						if (floorDiffE1 > floorDiffE2) {
							e2.Post(pipeData);
							if (isInAutoMode) {
								e2.Post(20 + nextFloor);
							}
						}
						else {
							e1.Post(pipeData);
							if (isInAutoMode) {
								e1.Post(10 + nextFloor);
							}
						}
						floorDiffE1 = 10;
						floorDiffE2 = 10;
					}
				}
				floor = 0;
				factor = 0;
			}
		}

		
	}

	toE1.WaitForThread();
	toE2.WaitForThread();
	
	cout << "Exiting the program..." << endl;
	e1.WaitForProcess();
	e2.WaitForProcess();

	return 0;
}