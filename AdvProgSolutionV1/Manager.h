#pragma once
#include <iostream> //inputs/outputs
#include <iomanip>

#include <string> //strings

#include <stdlib.h> //standard library

#include "User.h"
#include "Tickets.h"
#include "eventSeat.h"
#include "Event.h"

//using namespace std;

class manager : public user //INHERITANCE
{

public:
	void displayProfile(tickets& ticketsClassObject) override; //ABSTRACTION override function for displaying certain user/manager profile including tickets
	void ticketMachineConfiguration(); //function to allow manager user to configure certain variables or arrays 


private: //ENCAPSULATION
	event eventClass; //[a form of CONSTRUCTORS - calls constructor of new class object]
	eventSeat eventSeatClass;
	tickets ticketsClass;
	user userClass;

	int userIndex; //index of chosen user so that their account details can be displayed to manager

	void viewUserAccounts(); //displays standard user account details
	void deleteConsumerAccount(); //deletes chosen standard user account
	void viewManagerAccounts(); //displays manager user account details
	void deleteManagerAccount(); //deletes manager user account
	void addManager(); //for adding a new manager account to system - only accessible by another manager account 

};