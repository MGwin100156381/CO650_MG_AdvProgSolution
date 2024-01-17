
#include "Tickets.h"


std::vector<std::string> tickets::temporaryTickets; //STATIC MEMEBER declaration
std::vector<std::string> tickets::userTickets; //STATIC MEMBER declaration


tickets::tickets() //CONSTRUCTOR initialization
{
	price = 10.00f;
	totalCost = 0;
	ticketCounter = 0;
	chosenTicket = 0;
	listCounter = 0;
}


void tickets::refundTicket() //refunds a chosen ticket
{
	chosenTicket = 0;
	listCounter = 1;
	bool doRefund = true;
	std::string continueRefund = "";


	while (userTickets.size() >= 1) //if user has any purchased tickets
	{
		displayTickets();

		while (doRefund == true) //while refunding do loop
		{
			while (chosenTicket < 1 || chosenTicket > userTickets.size())
			{
				system("cls");
				displayTickets();
				std::cout << "\n\nPlease choose the number of the ticket you wish to refund: ";
				std::cin >> chosenTicket;

				if (chosenTicket >= 1 && chosenTicket <= userTickets.size())
				{
					userTickets.erase(userTickets.begin() + (chosenTicket - 1)); //deletes chosen ticket (index) from tickets array
					system("cls");
					std::cout << "\nThis ticket has been refunded..." << std::endl;
					displayTickets();
					break;
				}

				else
				{
					std::cin.clear(); //clears input error
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears input buffer
				}
			}

			if (userTickets.size() >= 1)
			{
				do
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					system("cls"); //clears screen
					displayTickets();
					std::cout << "\nDo you wish to refund another ticket? Y/N: ";
					std::cin >> continueRefund;
				} while (continueRefund != "Y" && continueRefund != "y" && continueRefund != "N" && continueRefund != "n"); //loop until Y/N
			}

			else if (userTickets.size() < 1) //if user has no purchased tickets
			{
				continueRefund = "N";
			}

			if (continueRefund == "N" || continueRefund == "n") //if N then stop loop and return to menu
			{
				doRefund = false;
				system("cls");
				return;
			}

			else if (continueRefund == "Y" || continueRefund == "y")
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continueRefund = "";

				if (userTickets.size() < 1)
				{
					system("cls");
					std::cout << "\nYou currently do not have any tickets to refund...\n\n" << std::endl;
					break;
				}

				else if (userTickets.size() >= 1)
				{
					chosenTicket = 0;
					doRefund = true;
					system("cls");
					displayTickets();
				}
			}
		}
	}
}


void tickets::calculateCost(int row, int seatNumber) //calculates the cost of each ticket - is called each time a seat is chosen
{


	price = 10.0f;
	if (row == 1 || row == 2) //prices based on which row was chosen
	{
		price += 15.00f;
	}

	else if (row >= 3 && row <= 5)
	{
		price += 7.50f;
	}

	else if (row > 5)
	{
		price = 10.00f;
	}

	price = applyDiscount(price); //FUNCTIONAL POINTER & POLYMORPHISM applies the discount set by manager user
	totalCost += price; // for displaying the total cost


	price = roundf(price * 100.0f) / 100.0f; // rounds to 2 decimal places

	std::ostringstream floatToString; //converts price float to a string 
	floatToString << std::fixed << std::setprecision(2) << price; //2 decimal places
	priceToString = floatToString.str(); 


	temporaryTickets.push_back(priceToString); //adds to temporary array so if purchase confirmed then adds to permanent array in Consumer.h and can be cleared

	std::cout << "\nTicket " << seatNumber - 1 << " Price: \x9c" << price << std::endl; //shows ticket price
	return;
}


void tickets::setDiscountPercentage() //FUNCTIONAL POINTERS & POLYMOPRHISM allows manager user to set a discount for the purchase
{
	float discountPercentage = 0;
	std::string discountChoice;

	while (discountChoice != "Y" && discountChoice != "y" && discountChoice != "N" && discountChoice != "n")
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\nWould you like apply a discount to your purchase? Y/N: ";
		std::cin >> discountChoice;
	}

	if (discountChoice == "Y" || discountChoice == "y")
	{
		while (std::cin.fail() || discountPercentage < 1 || discountPercentage > 100)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nPlease enter the discount percentage you wish to apply: ";
			std::cin >> discountPercentage;
		}
	}


	setDiscountPointer([discountPercentage](float price)  //FUNCTIONAL POINTERS & POLYMORPHISM returns price that has been altered by entered discount percentage
	{
		return price - (price * (discountPercentage / 100.0f));
	});
}