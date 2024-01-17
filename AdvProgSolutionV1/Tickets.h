#pragma once
#include <iostream> //inputs/outputs
#include <iomanip>

#include <string> //strings
#include <sstream> 

#include <stdlib.h> //standard library

#include <vector> //vector arrays 

#include <functional> //relating to functional pointers

#include "User.h"

//using namespace std;

class user; //FRIENDSHIP forward declaration


class tickets
{

private: //ENCAPSULATION
	using DiscountPointer = std::function<float(float)>; //FUNCTIONAL POINTERS & POLYMORPHISM - type (not object) for functional pointer that can be held as a variable and used as a pointer to a function
	DiscountPointer discountPointer; //FUNCTIONAL POINTERS & POLYMORPHISM actual variable for functional pointer type that points to a function

	int ticketCounter; //for counting number of tickets purchased
	int chosenTicket; //menu choice - reset to 0 so doesn't break loop
	int listCounter; //for iterating through tickets and displaying ticket ID

	std::string confirmPurchase = "";
	std::string priceToString = "";
	std::string floatConvert = "";

	static std::vector<std::string> temporaryTickets; //STATIC MEMBER so that it is saved across functions - private because used as temp storage



public:
	tickets(); //CONSTRUCTOR

	float price = 10.00; //base price of tickets
	float totalCost; //total cost of all tickets purchased

	static std::vector<std::string> userTickets; //STATIC so that is is saved across functions - public because is permanent array
	
	void calculateCost(int, int); //calculates the cost of each ticket
	void displayTickets(); //displays purchased tickets
	void refundTicket(); //refunds chosen ticket 

	void setDiscountPercentage(); //FUNCTIONAL POINTERS & POLYMORPHISM allows manager set a discount for the ticket purchase


	void setDiscountPointer(const DiscountPointer& newPointer) //FUNCTIONAL POINTERS & POLYMORPHISM
	{
		discountPointer = newPointer; //sets the discountPointer pointer to the pointer parameter that has been passed
	}

	float applyDiscount(float originalPrice) //FUNCTIONAL POINTERS & POLYMORPHISM
	{
		if (discountPointer) //if discountPointer is actually pointing to a function (not null)
		{
			return discountPointer(originalPrice); //passes originalPrice parameter through the function pointed to by discountPointer and returns float result
		}
		return originalPrice; //discountPointer is null then return parameter (no change)
	}




	bool purchaseReceipt(user& userClassObject) //FRIENDSHIP
	{
		ticketCounter = 1;

		do
		{
			std::cout << "Do you wish to confirm this purchase? Y/N "; //keep asking for Y/y  /  N/n
			std::cin >> confirmPurchase;
		} while (confirmPurchase != "Y" && confirmPurchase != "y" && confirmPurchase != "N" && confirmPurchase != "n");


		if (userClassObject.consumerAges[userClassObject.userEmailIndex] < 18) //if user is under 18 then cancel purchase
		{
			std::cout << "You must be 18 or over to purchase a ticket... this selection has been cancelled...\n " << std::endl;
			return false;
		}

		else if (userClassObject.consumerAges[userClassObject.userEmailIndex] >= 18) //if user is over 18 then continue purchase
		{
			if (confirmPurchase == "Y" || confirmPurchase == "y") //confirm purchase
			{
				system("cls");
				std::cout << "\nThis purchase has been confirmed, here is your receipt: \n" << std::endl;
				std::cout << "\n\t\tRECEIPT: \n";

				for (int i = 0; i < (temporaryTickets.size()); i++) //for each ticket purchased
				{
					userTickets.push_back(std::string(temporaryTickets[i]));
					std::cout << "\n\tTicket " << ticketCounter << ":\t\x9c" << std::fixed << std::setprecision(2) << temporaryTickets[i]; //display ticket and price to 2dp
					ticketCounter++;
				}

				std::cout << "\n\t----------------------";
				std::cout << "\n\n\tTotal: \t\t\x9c" << totalCost << "\n\n" << std::endl; //total cost
				totalCost = 0; //reset total cost for any future transactions
				temporaryTickets.clear(); //clears temporary tickets for any future transactions
				return true;
			}

			else if (confirmPurchase == "N" || confirmPurchase == "n") //cancel purchase
			{
				std::cout << "\nThis purchase has been cancelled..." << std::endl;
				temporaryTickets.clear();
				price = 0; //resets price for later use
				totalCost = 0; //resets total cost so does not stack over time
				return false;
			}
		}
	}
};