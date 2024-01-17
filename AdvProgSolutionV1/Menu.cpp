
#include "Menu.h"


void menu::mainMenu() //main menu for standard users
{
	while (menuEnd != true)
	{
		int menuOption = 0; //used for the switch

		std::cout << "\n\n\n\033[1;37mTicket Machine Main Menu" << std::endl;
		std::cout << "\t\t1: Current Events\n ";
		std::cout << "\t\t2: View Profile\n";
		std::cout << "\t\t3: Exit\n\033[0m";
		std::cout << "Please choose one of the options above: ";
		std::cin >> menuOption;

		while (std::cin.fail() || menuOption < 1 || menuOption > 3)
		{
			std::cin.clear(); //clears input error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears input buffer
			std::cout << "Please choose from the options stated: ";
			std::cin >> menuOption;
		}

		switch (menuOption)
		{
		case 1: //display events & get event choice
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls"); //clears screen
			eventClass.displayEvents();
			break;


		case 2: //display standard user profile
			system("cls");
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			userClass.displayProfile(ticketsClass);
			break;


		case 3: //exit program
			system("cls");
			std::cout << "\n\n\n\t\t\t\t\033[31mYou have exited the program.\n\n\033[0m" << std::endl;
			exit(0);
			break;


		default:
			std::cout << "Please choose from the options stated: ";
			std::cin.get();
		};
	}
}


void menu::mainMenu(bool isManager) //OVERLOADING main menu for manager users
{
	while (menuEnd != true)
	{
		int menuOption = 0; //used for the switch

		//system("cls");
		std::cout << "\n\n\n\033[1;37mTicket Machine Main Menu" << std::endl;
		std::cout << "\t\t1: Current Events\n ";
		std::cout << "\t\t2: View Profile\n";
		std::cout << "\t\t3: System Configuration\n";
		std::cout << "\t\t4: Exit\n\033[0m";
		std::cout << "Please choose one of the options above: ";
		std::cin >> menuOption;
		while (std::cin.fail() || menuOption < 1 || menuOption > 4)
		{
			std::cin.clear(); //clears input error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears input buffer
			std::cout << "Please choose from the options stated: ";
			std::cin >> menuOption;
		}

		switch (menuOption)
		{
		case 1: //display events & get event choice
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			eventClass.displayEvents();
			break;

		case 2: //display manager user profile
			system("cls");
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			userClass.isManager = isManager;
			managerClass.displayProfile(ticketsClass);
			break;

		case 3: //allow manager to configure some ticket machine elements
			system("cls");
			managerClass.ticketMachineConfiguration();
			break;

		case 4: //exit program
			system("cls");
			std::cout << "\n\n\n\t\t\t\t\033[31mYou have exited the program.\n\n\033[0m" << std::endl;
			exit(0);
			break;

		default:
			std::cout << "Please choose from the options stated: ";
			std::cin.get();
		};
	}
}


void menu::loginEmail() //asks user for login email
{
	std::string emailInput;
	std::string passwordInput;
	bool emailFound = false;
	bool passwordFound = false;
	isManager = false;


	userClass.userEmailIndex = -1;
	userClass.userPasswordIndex = -1;

	int incorrectEmailCount = 0; //failed email attempts
	int incorrectPasswordCount = 0;  //failed password attempts

	std::cout << "\nTo login please enter your login email: ";
	std::cin >> emailInput;
	while (!emailFound && incorrectEmailCount < 5) //do loop while email is invalid and invalid attempts less than 5
	{
		for (const auto& email : userEmails) //increment loops through values in userEmails array
		{
			userClass.userEmailIndex += 1;
			if (emailInput == email)
			{
				emailFound = true;
				loginPassword();
			}

			else if (emailInput != email)
			{
				for (const auto& email : managerEmails)
				{
					if (emailInput == email)
					{
						isManager = true;
						userClass.isManager = isManager;
						emailFound = true;
						loginPassword();
					}
				}
			}
		}

		if (!emailFound) //if incorrect email then ask to reinput
		{
			incorrectEmailCount += 1;
			std::cout << "Invalid email..." << std::endl;
			std::cout << "Please re-enter your email: ";
			userClass.userEmailIndex = -1;
			std::cin >> emailInput;
		}
	}
	if (incorrectEmailCount >= 5) //if invalid email too many times then send back to initial window
	{
		system("cls");
		std::cout << "\nToo many incorrect login attempts...\n\n" << std::endl;
		accountScreen();
	}
}

void menu::loginPassword() //asks user for login password
{
	std::string passwordInput;
	int incorrectPasswordCount = 0;
	bool passwordFound = false;

	std::cout << "Please enter your account password: ";
	std::cin >> passwordInput;

	while (!passwordFound && incorrectPasswordCount < 5)
	{
		for (const auto& password : userPasswords)
		{
			userClass.userPasswordIndex += 1;
			if (passwordInput == password && userClass.userPasswordIndex == userClass.userEmailIndex) //checks if the input is correct and matches the index of the email input
			{
				passwordFound = true;
				login();
			}

			else if (passwordInput != password)
			{
				for (const auto& password : managerPasswords)
				{
					if (passwordInput == password)
					{
						isManager = true;
						passwordFound = true;
						login(isManager);
					}
				}
			}
		}

		if (!passwordFound) //if incorrect password then ask to reinput
		{
			incorrectPasswordCount += 1; //counter
			std::cout << "Incorrect password please try again..." << std::endl;
			std::cout << "Please re-enter your password: ";
			userClass.userPasswordIndex = -1;
			std::cin >> passwordInput;
		}
	}

	if (incorrectPasswordCount >= 5) //if invalid password too many times then send back to initial window
	{
		system("cls");
		std::cout << "\nToo many incorrect login attempts...\n\n" << std::endl;
		accountScreen();
	}
}



void menu::login() //verifies correct login and sends to standard user main menu
{
	loggedIn = true;
	system("cls"); //clear text on screen
	std::cout << "You have successfully logged in.\n\n";
	std::cin.ignore();
	std::cout << "Press enter to continue... ";
	std::cin.get();
	mainMenu();
}


void menu::login(bool isManager) //OVERLOADING verifies correct login and send to manager user main menu
{
	loggedIn = true;
	system("cls"); //clear text on screen
	std::cout << "You have successfully logged in as a Manager.\n\n";
	std::cin.ignore();
	std::cout << "Press enter to continue... ";
	std::cin.get();
	mainMenu(isManager);
}



void menu::makeAccount() //allows the user to create a new account
{
	std::string newEmail;
	std::string newPassword;
	std::string confirmAccount;
	bool emailAt, emailDot, emailExists;

	std::cout << std::endl;
	while (true)
	{
		do //checks if input contains "@" and "." and is not already registered
		{
			emailAt = false;
			emailDot = false;
			emailExists = false;
			std::cin.clear();
			std::cin.ignore();
			std::cout << "To register please enter your email: ";
			std::cin >> newEmail;
		
			for (char i : newEmail)
			{
				if (i == '@')
				{
					emailAt = true;
				}

				else if (i == '.')
				{
					emailDot = true;
				}

			}

			for (const auto& existingEmail : userEmails)
			{
				if (newEmail == existingEmail)
				{
					std::cout << "\nThat email already has a registered account...\n\n" << std::endl;
					emailExists = true;
				}
			}

		} while (std::cin.fail() || (emailAt != true || emailDot != true) || emailExists == true);

		std::cout << std::endl;

		do
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "To register please enter your password: ";
			std::cin >> newPassword;
		} while (std::cin.fail());

		std::cout << std::endl;

		do
		{
			system("cls");
			std::cout << "\n\tEmail:     " << newEmail << "\n\tPassword:  " << newPassword << std::endl;
			std::cout << "\nAre these details correct? Y/N:";
			std::cin >> confirmAccount;
		} while (confirmAccount != "Y" && confirmAccount != "y" && confirmAccount != "N" && confirmAccount != "n");
		
		if (confirmAccount == "Y" || confirmAccount == "y")
		{
			system("cls");
			std::cout << std::endl;
			break;
		}
		system("cls");
		std::cout << std::endl;
	}

	userEmails.push_back(newEmail); //add input email to end of emails vector array
	userClass.userEmailIndex = (userEmails.size() - 1); //reassign value for email index so profile details are updated + displayed properly (setProfile())
	
	userPasswords.push_back(newPassword);//add input password to end of passwords vector array
	std::cout << std::endl;

	userClass.setProfile(isManager); //sets the user profile details

	system("cls");
	std::cout << "You have succesfully registered an account! " << std::endl;
	loginEmail(); //at this point user registered new account so start login
}


void menu::accountScreen() //asks user to register or log in
{
	std::string accountCheck; //to check if user has account

	std::cout << "\nWelcome to this prototype Ticket Machine. \n";
	std::cout << "You must log in to use this system.\n";
	std::cout << "Do you have an account? Y/N: " << accountCheck; //check if they have account
	while (accountCheck != "Y" || accountCheck != "N" || accountCheck != "n" || accountCheck != "y")   //while invalid input ask for input
	{
		std::cout << "Please enter Y/y (Yes) if you have an account or N/n (No) if you do not: ";
		std::cin >> accountCheck;

		if (accountCheck == "Y" || accountCheck == "y")    //if user has account then login
		{
			loginEmail();
		}

		else if (accountCheck == "N" || accountCheck == "n")   //if user has no account then register
		{
			makeAccount();
		}

		else
		{
			std::cout << "Incorrect Input\n";   //if not Y/y or N/n then invalid
		}
	};

	if (accountCheck == "N" || accountCheck == "n") //if user has no account then register
	{
		makeAccount();
	}
}