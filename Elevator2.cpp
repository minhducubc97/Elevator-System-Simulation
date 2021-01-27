#include "../rt.h"
#include "../Elevator.h"

CRendezvous startProgram("StartProgram", 4);
elevatorData elevator;
CMailbox myMailBox;
ElevatorStatus e2Status;

int main(void) {
	int inProgress = true;
	UINT pipeData = 0;
	int floor = 0;
	int factor = 0;
	bool updateEData = false;
	bool isMoving = false;
	bool hasRemainingRequests = false;
	int elevatorTimer = 0;
	int doorTimer = 0;
	int timer = 0;
	bool isUnderMaintenance = false;

	elevator.currFloor = 0;
	elevator.active = false;
	elevator.door = CLOSED;
	elevator.direction = STATIC;
	for (int i = 0; i < 10; i++) {
		elevator.destFloors[i] = false;
	}
	e2Status.UpdateElevator2Status(elevator);

	startProgram.Wait();

	while (inProgress) {
		if (myMailBox.TestForMessage()) {
			pipeData = myMailBox.GetMessage();

			if (pipeData == END_GAME) {
				break;
			}
			else if (pipeData == E2_ERROR) {
				isUnderMaintenance = true;
				MOVE_CURSOR(0, 1);
				cout << "Elevator 2 is under maintenance!";
			}
			else if (pipeData == E2_FIXED) {
				isUnderMaintenance = false;
				MOVE_CURSOR(0, 1);
				cout << "Elevator 2 is now back to work !";
			}
			else {
				floor = pipeData % 10;
				factor = pipeData / 10;
				updateEData = true;

				if (!elevator.destFloors[floor]) {
					elevator.destFloors[floor] = true;
				}

				if (floor > elevator.currFloor) {
					elevator.direction = UP;
				}
				else if (floor < elevator.currFloor) {
					elevator.direction = DOWN;
				}
			}
		}

		if (!isUnderMaintenance) {
			if (updateEData) {
				updateEData = false;
				e2Status.UpdateElevator2Status(elevator);
			}

			if (!elevator.active && elevator.currFloor != floor) {
				elevator.active = true;
				if (floor > elevator.currFloor) {
					elevator.direction = UP;
					isMoving = true;
				}
				else if (floor < elevator.currFloor) {
					elevator.direction = DOWN;
					isMoving = true;
				}
				updateEData = true;
			}

			if (elevator.active && elevator.currFloor == floor && elevator.door == CLOSED) {
				elevator.door = OPEN;
				elevator.destFloors[floor] = false;
				updateEData = true;
				hasRemainingRequests = false;

				if (elevator.direction == UP) {
					for (int i = elevator.currFloor + 1; i < 10; i++) {
						if (elevator.destFloors[i] == true) {
							floor = elevator.destFloors[i];
							hasRemainingRequests = true;
						}
					}
					if (!hasRemainingRequests) {
						elevator.active = false;
						elevator.direction = STATIC;
					}
				}
				else if (elevator.direction == DOWN) {
					for (int i = elevator.currFloor - 1; i >= 0; i--) {
						if (elevator.destFloors[i] == true) {
							floor = elevator.destFloors[i];
							hasRemainingRequests = true;
						}
					}
					if (!hasRemainingRequests) {
						elevator.active = false;
						elevator.direction = STATIC;
					}
				}
				else {
					elevator.active = false;
				}
			}

			if (elevator.door == OPEN) {
				doorTimer++;
			}
			if (doorTimer >= 3000) {
				doorTimer = 0;
				updateEData = true;
				elevator.door = CLOSED;

				if (elevator.direction != STATIC) {
					isMoving = true;
				}
			}

			if (isMoving) {
				elevatorTimer++;
			}
			if (elevatorTimer >= 1000) {
				elevatorTimer = 0;
				updateEData = true;
				if (elevator.currFloor == floor) {
					isMoving = false;
				}
				if (elevator.direction == UP) {
					elevator.currFloor++;
				}
				else if (elevator.direction == DOWN) {
					elevator.currFloor--;
				}
			}

			if (timer >= 1000) {
				MOVE_CURSOR(0, 0);
				if (elevator.active) {
					cout << "Current status of the elevator 2: Active      " << endl;
				}
				else {
					cout << "Current status of the elevator 2: Not active  " << endl;
				}
				cout << "Current floor: " << elevator.currFloor << "               " << endl;
				if (elevator.direction == UP) {
					cout << "Current direction: UP                         " << endl;
				}
				else if (elevator.direction == DOWN) {
					cout << "Current direction: DOWN                       " << endl;
				}
				else {
					cout << "Current direction: STATIC                     " << endl;
				}
				cout << "Destination floors: ";
				for (int i = 0; i < 10; i++) {
					if (elevator.destFloors[i]) {
						cout << i << " ";
					}
				}
				cout << "" << endl;
				if (elevator.door == OPEN) {
					cout << "Current state of the door: OPEN               " << endl;
				}
				else {
					cout << "Current state of the door: CLOSED             " << endl;
				}				
				if (elevator.maintenance) {
					cout << "Elevator under maintenance                    " << endl;
				}
				else {
					cout << "                                              " << endl;
				}
			}

			timer++;
		}
	}

	return 0;
}