#pragma once
#include <iostream> //inputs/outputs
#include <iomanip>

#include <string> //strings

#include <stdlib.h> //standard library

#include <vector> //vector arrays

#include "eventSeat.h" 

//using namespace std;

class event
{

public:
	void displayEvents(); //displays events stored in vector arrays 
	void eventChoice(); //asks user to choose an event to display the details of


private: //ENCAPSULATION
	eventSeat eventSeatClass; //[a form of CONSTRUCTORS - calls constructor of new class object]

	int chooseEvent; //for user to choose an event to display seats

	//arrays relating to event details - vectors so that they can be expanded
	std::vector<std::string> eventNames = { "Zily" , "Jamman" , "Del" , "Joe Bricks" };
	std::vector<std::string> eventDates = { "01/01/2024" , "02/01/2024" , "03/01/2024" , "04/01/2024" };
	std::vector<std::string> eventTimes = { "13:00 - 14:30", "15:00 - 16:30" , "17:00 = 18:30" , "20:00 - 21:30" };

};