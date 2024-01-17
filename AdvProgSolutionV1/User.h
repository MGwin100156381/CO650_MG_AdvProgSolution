#pragma once
#include <iostream> //input/outputs
#include <iomanip> 

#include <string> //strings
#include <sstream> 

#include <stdlib.h> //standard library

#include <vector> //vector arrays

#include <chrono> //time & date
#include <ctime>

#include <cctype> //char handling

#include <algorithm> //std::all_of for input format validation

//using namespace std;

class tickets; //FRIENDSHIP forward declaration


class user
{

public:
	user(); //CONSTRUCTOR

	friend class tickets; //FRIENDSHIP friend class

	static bool isManager; //STATIC MEMBER for validating if user is a manger or not
	static int userEmailIndex, userPasswordIndex; //STATIC MEMBER so they can be properly accessed and referenced in other classes and so 

	void setProfile(bool); //setting account details
	virtual void displayProfile(tickets& ticketsClassObject); //VIRTUAL (ABSTRACTION) function to display user profile including tickets


protected: //ENCAPSULATION
	//arrays relating to consumer (standard user) account details - vectors so that they can be expanded
	std::vector<std::string> consumerFirstNames = { "Postman", "John", "Marco", "Polo", "d" };
	std::vector<std::string> consumerLastNames = { "Pat", "Smith", "Polo" , "Marco", "d" };
	std::vector<int> consumerAges = { 42, 20, 58, 85, 100 };
	std::vector<std::string> consumerAddresses = { "RM Avenue", "Johnny Grove", "Marco Street", "Polo Street", "d" };
	std::vector<std::string> consumerDOBs = { "06/09/1981", "01/01/2003", "06/06/1965", "07/07/1938", "12/12/1923" };

	//arrays relating to manager account details
	std::vector<std::string> managerFirstNames = { "ManagerFirstName" };
	std::vector<std::string> managerLastNames = { "ManagerLastName" };
	std::vector<int> managerAges = { 111 };
	std::vector<std::string> managerAddresses = { "ManagerStreet" };
	std::vector<std::string> managerDOBs = { "12/12/1912" };


private: //ENCAPSULATION
	int currentYear, currentMonth, currentDay; //current date so user age can be validated

	void getCurrentDate(int& year, int& month, int& day); //gets current date

};