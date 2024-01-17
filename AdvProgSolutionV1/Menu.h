#pragma once
#include <iostream> //inputs/outputs
#include <iomanip>
 
#include <string> //strings

#include <stdlib.h> //standard library

#include <vector> //vector arrays

#include "User.h"
#include "eventSeat.h"
#include "Event.h"
#include "Tickets.h"
#include "Manager.h"

//using namespace std;

class menu : public manager //INHERITANCE
{

public: 

	menu() //CONSTRUCTOR
	{
		isManager = false;
	}

	bool isManager; //for validating if the logged in user is a manager or not

	void accountScreen(); //initial menu where user is prompted to log in or register
	void makeAccount(); //function for registering new account
	void loginEmail(); //validating input login email
	void loginPassword(); //validating input login password
	void login(); //logs in standard user
	void login(bool); //OVERLOADING logs in a manager user
	void mainMenu(); //displaying regular main menu to standard user
	void mainMenu(bool); //OVERLOADING displaying special main menu to manager user


protected: //ENCAPSULATION
	//vector arrays for standard user account login details
	std::vector<std::string> userEmails = { "Email@Gmail.com", "User@Gmail.com", "Name@Gmail.com", "Login@Gmail.com", "d"};  //login emails  - vector so can be expanded
	std::vector<std::string> userPasswords = { "Password", "Correct", "Enter", "Dog", "d"}; //login passwords
	
	//vector arrays for manager user account login details
	std::vector<std::string> managerEmails = { "Manager1" };
	std::vector<std::string> managerPasswords = { "Manager1" };


private: //ENCAPSULATION
	event eventClass; //[a form of CONSTRUCTORS - calls constructor of new class object]
	eventSeat eventSeatClass;
	manager managerClass;
	tickets ticketsClass;
	user userClass;

	bool loggedIn = false; // if true then can login else must make account/quit
	bool menuEnd; //ensures menu continues to loop after other functions end

};