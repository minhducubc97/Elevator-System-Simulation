#include <stdio.h>
#include "../Elevator.h"
#include "../rt.h"
#include "../Dispatcher/Passenger.h"

CMutex* console; // can be CSemaphore too
CTypedPipe<int> i2d("IOToDispatcherPipe", 1024);
CTypedPipe<passengerData> p2i("ToIOPipe", 1024);
CMailbox myMailBox;
CRendezvous startProgram("StartProgram", 4);
elevatorData elevator1Data;
elevatorData elevator2Data; 
ElevatorStatus e1Status;
ElevatorStatus e2Status;

bool inProgress;
bool isInAutoMode;

void drawElevatorSystemFrame() {
	console->Wait();
	MOVE_CURSOR(0, 1);
	cout << "===================================";
	MOVE_CURSOR(0, 2);
	cout << "Floor 9:";
	MOVE_CURSOR(0, 3);
	cout << "===================================";
	MOVE_CURSOR(0, 4);
	cout << "Floor 8:";
	MOVE_CURSOR(0, 5);
	cout << "===================================";
	MOVE_CURSOR(0, 6);
	cout << "Floor 7:";
	MOVE_CURSOR(0, 7);
	cout << "===================================";
	MOVE_CURSOR(0, 8);
	cout << "Floor 6:";
	MOVE_CURSOR(0, 9);
	cout << "===================================";
	MOVE_CURSOR(0, 10);
	cout << "Floor 5:";
	MOVE_CURSOR(0, 11);
	cout << "===================================";
	MOVE_CURSOR(0, 12);
	cout << "Floor 4:";
	MOVE_CURSOR(0, 13);
	cout << "===================================";
	MOVE_CURSOR(0, 14);
	cout << "Floor 3:";
	MOVE_CURSOR(0, 15);
	cout << "===================================";
	MOVE_CURSOR(0, 16);
	cout << "Floor 2:";
	MOVE_CURSOR(0, 17);
	cout << "===================================";
	MOVE_CURSOR(0, 18);
	cout << "Floor 1:";
	MOVE_CURSOR(0, 19);
	cout << "===================================";
	MOVE_CURSOR(0, 20);
	cout << "Ground floor:";		
	MOVE_CURSOR(0, 25);
	cout << "Entered command:";
	MOVE_CURSOR(0, 30);
	cout << "Info:";
	console->Signal();
}

UINT __stdcall drawElevator1(void *args) {
	while (inProgress) {
		elevator1Data = e1Status.IOGetElevator1Status();

		console->Wait();
		MOVE_CURSOR(15, 2);
		if (elevator1Data.currFloor == 9) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 8
		MOVE_CURSOR(15, 4);
		if (elevator1Data.currFloor == 8) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 7
		MOVE_CURSOR(15, 6);
		if (elevator1Data.currFloor == 7) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 6
		MOVE_CURSOR(15, 8);
		if (elevator1Data.currFloor == 6) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 5
		MOVE_CURSOR(15, 10);
		if (elevator1Data.currFloor == 5) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 4
		MOVE_CURSOR(15, 12);
		if (elevator1Data.currFloor == 4) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 3
		MOVE_CURSOR(15, 14);
		if (elevator1Data.currFloor == 3) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 2
		MOVE_CURSOR(15, 16);
		if (elevator1Data.currFloor == 2) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 1
		MOVE_CURSOR(15, 18);
		if (elevator1Data.currFloor == 1) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 0
		MOVE_CURSOR(15, 20);
		if (elevator1Data.currFloor == 0) {
			if (elevator1Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator1Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}
		MOVE_CURSOR(20, 50);
		console->Signal();
		SLEEP(100);
	}
	return 0;
}

UINT __stdcall drawElevator2(void *args) {
	while (inProgress) {
		elevator2Data = e2Status.IOGetElevator2Status();

		console->Wait();
		//FLOOR 9
		MOVE_CURSOR(25, 2);
		if (elevator2Data.currFloor == 9) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 8
		MOVE_CURSOR(25, 4);
		if (elevator2Data.currFloor == 8) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
		cout << "|   |     ";
		}

		//FLOOR 7
		MOVE_CURSOR(25, 6);
		if (elevator2Data.currFloor == 7) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 6
		MOVE_CURSOR(25, 8);
		if (elevator2Data.currFloor == 6) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 5
		MOVE_CURSOR(25, 10);
		if (elevator2Data.currFloor == 5) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 4
		MOVE_CURSOR(25, 12);
		if (elevator2Data.currFloor == 4) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 3
		MOVE_CURSOR(25, 14);
		if (elevator2Data.currFloor == 3) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 2
		MOVE_CURSOR(25, 16);
		if (elevator2Data.currFloor == 2) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 1
		MOVE_CURSOR(25, 18);
		if (elevator2Data.currFloor == 1) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		//FLOOR 0
		MOVE_CURSOR(25, 20);
		if (elevator2Data.currFloor == 0) {
			if (elevator2Data.maintenance) {
				cout << "||x||     ";
			}
			else if (elevator2Data.door == OPEN)
				cout << "||O||     ";
			else
				cout << "|||||     ";
		}
		else
		{
			cout << "|   |     ";
		}

		MOVE_CURSOR(20, 50);
		console->Signal();
		SLEEP(100);
	}
	return 0;
}

//UINT __stdcall createPassengers(void *args) {
//	while (isInAutoMode) {
//		int randWaitTime = (rand() % 10) *1000;
//		Passenger* newPass = new Passenger();
//		newPass->Resume();
//		newPass->WaitForThread();
//		delete newPass;
//		SLEEP(randWaitTime);
//	}
//	return 0;
//}

int main(void) {
	int randWaitTime = (rand() % 10) * 1000;
	string command;
	int code = 0;
	UINT message = 1;
	isInAutoMode = false;
	inProgress = true;
	passengerData newPass = {
		0,
		0,
		false
	};
	console = new CMutex("console");

	startProgram.Wait();

	drawElevatorSystemFrame();
	CThread toE1(drawElevator1, ACTIVE, NULL);
	CThread toE2(drawElevator2, ACTIVE, NULL);

	while (inProgress) {
		if (TEST_FOR_KEYBOARD() != 0) {
			cin >> command;

			console->Wait();
			MOVE_CURSOR(20, 25);
			cout << command << "     ";
			if (command.length() == 2) {
				if (command == "ee") {
					i2d.Write(&END_GAME);
				}
				else if (command == "-1") {
					MOVE_CURSOR(8, 30);
					cout << "Elevator 1 is under maintenance!                   ";
					i2d.Write(&E1_ERROR);
				}
				else if (command == "-2") {

					MOVE_CURSOR(8, 30);
					cout << "Elevator 2 is under maintenance!                   ";
					i2d.Write(&E2_ERROR);
				}
				else if (command == "+1") {
					MOVE_CURSOR(8, 30);
					cout << "Elevator 1 is back to work!                        ";
					i2d.Write(&E1_FIXED);
				}
				else if (command == "+2") {
					MOVE_CURSOR(8, 30);
					cout << "Elevator 2 is back to work!                        ";
					
				}
				else if (command == "d+") {
					MOVE_CURSOR(8, 30);
					cout << "Dynamic Passengers functionality activated!        ";
					isInAutoMode = true;
				}
				else if (command == "d-") {
					MOVE_CURSOR(8, 30);
					cout << "Dynamic Passengers functionality deactivated!      ";
					isInAutoMode = false;
				}
				else if (isdigit(command[0]) && isdigit(command[1]) && stoi(command) >= 10 && stoi(command) < 20) {
					MOVE_CURSOR(8, 30);
					cout << "An inside request from Elevator 1 has been made!   ";
					code = stoi(command);
					i2d.Write(&code);
				}
				else if (isdigit(command[0]) && isdigit(command[1]) && stoi(command) >= 20 && stoi(command) < 30) {
					MOVE_CURSOR(8, 30);
					cout << "An inside request from Elevator 2 has been made!   ";					
					code = stoi(command);
					i2d.Write(&code);
				}
				else if (command[0] == 'u' && isdigit(command[1]) && command[1] - '0' < 10 && command[1] - '0' >= 0) {
					MOVE_CURSOR(8, 30);
					cout << "An outside request to go up has been made!         ";
					code = 900 + command[1] - '0';

					i2d.Write(&code);
				}
				else if (command[0] == 'd' && isdigit(command[1]) && command[1] - '0' < 10 && command[1] - '0' >= 0) {
					MOVE_CURSOR(8, 30);
					cout << "An outside request to go down has been made!       ";
					code = 100 + command[1] - '0';
					i2d.Write(&code);
				}
				else {
					MOVE_CURSOR(8, 30);
					cout << "Invalid command!                                   ";
				}
				command = "  ";
			}
			else {
				MOVE_CURSOR(8, 30);
				cout << "Invalid command!                                   ";
			}
			MOVE_CURSOR(20, 25);
			console->Signal();
		}

		//if (isInAutoMode) {
		//	if (randWaitTime == 0) {
		//		Passenger* newPassObj = new Passenger();
		//		newPassObj->Resume();
		//		newPassObj->WaitForThread();
		//		delete newPassObj;
		//		randWaitTime = (rand() % 10) * 1000;
		//	}
		//	randWaitTime--;

		//	if (p2i.TestForData() >= 0) {
		//		p2i.Read(&newPass);
		//		if (newPass.isGoUp) {
		//			code = SEQ_UPSTAIR_REQUEST * 10 + newPass.destFloor * 10 + newPass.currFloor;
		//		}
		//		else {
		//			code = SEQ_DOWNSTAIR_REQUEST * 10 + newPass.destFloor * 10 + newPass.currFloor;
		//		}
		//		i2d.Write(&code);
		//	}
		//}

		if (myMailBox.TestForMessage()) {
			message = myMailBox.GetMessage();
			if (message == END_GAME) {
				console->Wait(); 
				MOVE_CURSOR(8, 30);
				cout << "Program finished!                                  ";
				console->Signal();
				inProgress = false;
				SLEEP(3000);
				break;
			}
		}
	}

	toE1.WaitForThread();
	toE2.WaitForThread();
	cout << "Exiting the program..." << endl;
	return 0;
}