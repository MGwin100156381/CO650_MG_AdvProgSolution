#pragma once
#include <iostream> //inputs/outputs
#include <iomanip>

#include <string> //strings

#include <stdlib.h> //standard library

#include <vector> //vector arrays 

#include "Tickets.h"
#include "User.h"

//using namespace std;

#define ANSI_RESET   "\033[0m" //ANSI codes for formatting text (colours)
#define ANSI_RED     "\033[31m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_YELLOW  "\033[33m"


class eventSeat
{

public:
	eventSeat(); //CONSTRUCTOR

	int rowCheck, columnCheck; //for checking if the seat chosen by user is valid
	
	void seatingPlan(); //calls functions relevant to the chosen event seating plan
	void displaySeats(); //displays seating plan to the user
	void chooseSeats(bool); //asks user to choose a seat from the seating plan


protected: //ENCAPSULATION
	char seatPlan[10][10]; //seating grid (10x10)

	int rows, columns; //number of rows //number of columms
	int seatAmount; //number of seats user wants 
	int ticketCounter; //for counting number of tickets purchased

	float price = 10.00; //default ticket price
	float totalCost; //cost of all tickets purchased 

	bool exitChoice; //whether user wants to exit menu

	std::string confirmPurchase; //whether user wants to confirm ticket purchase
	std::string choice; //the actual choice input that determines exitChoice true/false (while loop)


private: //ENCAPSULATION
	tickets ticketsClass; //[a form of CONSTRUCTORS - calls constructor of new class object]
	user userClass;

	int seatCounter; //a counter for displaying correct number in a loop
	int rowChosen, columnChosen; //when user selects row //when user selects column

	bool purchaseConfirmed; //whether the ticket purchase has been confirmed

	std::vector<float> temporaryTickets; //so it can be added to consumerClass.tickets after purchase confirmed then cleared / if cancelled then cleared so can be reused. - vector so can be expanded
	
	void initializeSeats(); //assigns a value to seat arrays so they can be displayed properly and resets variables
	void randomSeats(); //this is for demonstration purposes - it changes a random selection of seats to 'T' for taken
	
};