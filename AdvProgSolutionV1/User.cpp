
#include "User.h"
#include "Tickets.h"


int user::userEmailIndex; //STATIC MEMBER declaration
int user::userPasswordIndex; //STATIC MEMBER declaration
bool user::isManager; //STATIC MEMBER declaration


user::user() //CONSTRUCTOR intialisation
{
	getCurrentDate(currentYear, currentMonth, currentDay); //gets current date
	userEmailIndex = 0;
	userPasswordIndex = 0;
}


void user::getCurrentDate(int& year, int& month, int& day) //gets the current date so user age can be calculated
{
	std::time_t currentTime = std::time(nullptr);
	struct std::tm timeInfo;

	if (localtime_s(&timeInfo, &currentTime) == 0) //localtime_s required to prevent problems with threads
	{
		year = timeInfo.tm_year + 1900; //calculates how many years since 1900 because of built-in function (e.g 2023 = 123) then adds 1900 
		month = timeInfo.tm_mon + 1; //+1 because january (first month) = 0 
		day = timeInfo.tm_mday;
	}

	else //if there is some sort of problem with getting date then set date to default 01/01/2023
	{
		year = 2023; 
		month = 01;
		day = 01;
	}
}


void user::displayProfile(tickets& ticketsClassObject) //displays standard user account details (not manager)
{
	int profileChoice = 0; //for profile menu switch
	std::cout << "\n\t\033[1;37mPROFILE:\033[0m\n\n\tFirst Name:       " << consumerFirstNames[userEmailIndex];
	std::cout << "\n\tSurname:          " << consumerLastNames[userEmailIndex];
	std::cout << "\n\tAddress:          " << consumerAddresses[userEmailIndex];
	std::cout << "\n\tDate of Birth:\t  " << consumerDOBs[userEmailIndex] << std::endl;
	ticketsClassObject.displayTickets();


	std::cout << "\n\n\n\t\t\033[1;37m1: Edit Profile\n";
	std::cout << "\t\t2: Refund Ticket\n";
	std::cout << "\t\t3: Main Menu\n\033[0m";
	std::cout << "\n\nPlease choose from one of these menu options: ";
	std::cin >> profileChoice;

	while (std::cin.fail() || profileChoice < 1 || profileChoice > 3)
	{
		std::cin.clear(); //clears input error
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears input buffer
		std::cout << "Please choose from the options stated: ";
		std::cin >> profileChoice;
	}

	switch (profileChoice)
	{
	case 1: //change standard user account details
		setProfile(isManager);
		break;


	case 2: //refund a ticket

		if (size(ticketsClassObject.userTickets) < 1) //if user has no tickets then cancel
		{
			system("cls"); //clears screen
			std::cout << "\nYou do not currently have any tickets to refund..." << std::endl;
			displayProfile(ticketsClassObject);
		}

		else //allow user to refund tickets
		{
			ticketsClassObject.refundTicket();
			displayProfile(ticketsClassObject);
		}

		break;


	case 3: //return to main menu
		system("cls");
		break;


	default:
		std::cout << "Please choose from the options stated: ";
		std::cin.get();
	};
}


void user::setProfile(bool isManager) //sets all user account details if they are standard or manager
{
	bool dateFormat = false; //checks date is in correct format (dd/mm/yyyy)
	int day, month, year;
	char dateDivider1 , dateDivider2; //for checking date input is divided by 2 '/'
	std::string detailInput = " ";
	

	if (userEmailIndex > (consumerFirstNames.size()-1)) //if new account is registered then initalise new slots for new details
	{
		consumerFirstNames.push_back(" ");
		consumerLastNames.push_back(" ");
		consumerAges.push_back(0);
		consumerAddresses.push_back(" ");
		consumerDOBs.push_back(" ");
	}

	std::cin.ignore();

	do
	{
		std::cout << "Please enter your first name: ";
		std::getline(std::cin, detailInput);
	} while (std::cin.fail() || (!std::all_of(detailInput.begin(), detailInput.end(), ::isalpha) || detailInput.empty()));

	if (isManager) //if manager then change change manager profile
	{
		managerFirstNames[userEmailIndex] = detailInput;
	}

	else
	{
		consumerFirstNames[userEmailIndex] = detailInput;
	}



	do
	{
		std::cout << "Please enter your last name: ";
		std::getline(std::cin, detailInput); //assign to lastName variable in consumer class
	} while (std::cin.fail() || (!std::all_of(detailInput.begin(), detailInput.end(), ::isalpha) || detailInput.empty()));
	
	if (isManager) //if manager then change change manager profile
	{
		managerLastNames[userEmailIndex] = detailInput;
	}

	else
	{
		consumerLastNames[userEmailIndex] = detailInput;
	}



	do
	{
		std::cout << "Please enter your address: ";
		std::getline(std::cin, detailInput); // assign to userAddress variable in consumer class
	} while (std::cin.fail() || detailInput.empty());
	
	if (isManager) //if manager then change change manager profile
	{
		managerAddresses[userEmailIndex] = detailInput;
	}

	else
	{
		consumerAddresses[userEmailIndex] = detailInput;
	}



	do
	{
		std::cin.clear();
		std::cout << "Please enter your date of birth in DD/MM/YYYY format: ";
		std::getline(std::cin, detailInput);
		std::istringstream dateInput(detailInput);

		if ( (dateInput >> day >> dateDivider1 >> month >> dateDivider2 >> year) && //checks input is dd/mm/yyyy format
			(dateDivider1 == '/' && dateDivider2 == '/') && //checks if seperated by '/'
			(day >= 1 && day <= 31) && //checks day is between 1 and 31 
			(month >= 1 && month <= 12) && //checks month is between 1 and 12
			!((month == 2 && day > 28) || (month != 2 && day > 31)) && //checks data is not february 29/30/31 - does not account for leap years (i cba)
			(year >= (currentYear - 125) && year <= currentYear) ) //checks user is not older than 125 or younger than 0
		{
			dateFormat = true;
		}
	} while (dateFormat != true);
	

	if (isManager) //if manager then change change manager profile
	{
		managerDOBs[userEmailIndex] = detailInput;
	}

	else
	{
		consumerDOBs[userEmailIndex] = detailInput;
	}



	if (currentMonth < month || (currentMonth == month && currentDay < day)) //if birthday has not passed then -1 year
	{
		year--;
	}


	if (isManager)
	{
		managerAges[userEmailIndex] = (currentYear - year);
		std::cout << managerAges[userEmailIndex];
	}

	else
	{
		consumerAges[userEmailIndex] = (currentYear - year);
		
	}
	system("cls");
}


void tickets::displayTickets() //displays all purchased tickets
{
	listCounter = 1;
	std::cout << "\n\t\033[1;37mTICKETS:       \033[0m\n";

	if (userTickets.size() < 1)
	{
		std::cout << "\t\t\033[31mNo Tickets.\033[0m" << std::endl;
	}

	else
	{
		for (const auto& ticket : userTickets) //displays current tickets
		{
			std::cout << "\n\t\t\033[1;33m Ticket " << listCounter << ": \x9c" << ticket << "\033[0m";
			listCounter++;
		}
		std::cout << std::endl;
	}
}