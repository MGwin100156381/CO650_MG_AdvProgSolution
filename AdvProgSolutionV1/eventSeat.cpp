
#include "eventSeat.h"


eventSeat::eventSeat() //CONSTRUCTOR initialization
{
	initializeSeats();
}


void eventSeat::initializeSeats() //initialization for seats 
{
	rows = 10;
	columns = 10; 
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			seatPlan[r][c] = 'A';
		}
	}
	randomSeats();
}


void eventSeat::randomSeats() //randomizes seats from A's to T's for demonstration purposes
{
	srand(static_cast<unsigned int>(time(0))); //generates random seed for rand() based on time of device so seed is always different

	int minimumPercentage = 35; //minimum percentage of seats that will be randomized
	int maximumPercentage = 80; //maximum percentage of seats that will be randomized
	int seatPercentage;

	do
	{
		seatPercentage = (rand() % (maximumPercentage - minimumPercentage + 1)) + minimumPercentage; //random number between max - min (+1 for correct range) and then add minimum so result is always between min and max
	} while (seatPercentage < minimumPercentage || seatPercentage > maximumPercentage || seatPercentage == 0);

	int numSeats = (rows * columns) / (100.0f/seatPercentage); //the number of seats that will be randomized (total number of seats / randomized percentage)
	int randomRow, randomColumn; //temp variables
	for (int i = 0; i < numSeats; i++)
	{
		randomRow = rand() % rows; //temp variable = random number between 0 - rows
		randomColumn = rand() % columns; //temp variable = random number between 0 - columns
		if (seatPlan[randomRow][randomColumn] != 'T')
		{
			seatPlan[randomRow][randomColumn] = 'T'; //changes A to T   
		}
		else // if it's already 'T', decrement i to pick another seat so that it always randomizes numSeats amount
		{
			i--;
		}
	}
}


void eventSeat::seatingPlan() //starts all of the seating arrangements
{
	displaySeats();
	chooseSeats(userClass.isManager);
}


void eventSeat::displaySeats() //displays all seats of an event in a grid 
{
	std::cout << "\n\t\t\t\t  COLUMNS\n\t|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  |\n"; //displays colums and a row of column numbers
	std::cout << "ROWS|   -------------------------------------------------------------\n";
	for (int r = 0; r < rows; r++)
	{
		std::cout << "   " << (r + 1) << "| \t|  "; //prints the number of the row at the side
		for (int c = 0; c < columns; c++) 
		{
			if (seatPlan[r][c] == 'A') 
			{
				std::cout << "\033[32m" << seatPlan[r][c] << "\033[0m  |  "; //set "A" to green
			}
			else if (seatPlan[r][c] == 'H') 
			{
				std::cout << "\033[1;33m" << seatPlan[r][c] << "\033[0m  |  "; //set "H" to yellow
			}
			else if (seatPlan[r][c] == 'T') 
			{
				std::cout << "\033[31m" << seatPlan[r][c] << "\033[0m  |  "; //set "T" to red
			}
			else //everything else is default colour
			{
				std::cout << seatPlan[r][c] << "  |  ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\t\t\033[32mA = Available\t  \033[31mT = Taken\t\033[1;33mH = Holding\033[0m" << std::endl;; //identification key for seats
	return;
}



void  eventSeat::chooseSeats(bool isManager) //after displaying seats, asks user to choose an available seat to purchase
{
	choice = ""; //resets choice for validation
	ticketCounter = 1; //for incrementing when displaying ticket number
	seatAmount = 0;
	seatCounter = 1;
	exitChoice = false;
	int seatsAvailable;

	while (exitChoice == false)
	{
		seatsAvailable = 0;
		for (int r = 0; r < rows; r++) //count number of available seats
		{
			for (int c = 0; c < columns; c++)
			{
				if (seatPlan[r][c] == 'A')
				{
					seatsAvailable++;
				}
			}
		}
		std::cout << "\n\nNumber of seats available: " << seatsAvailable << std::endl;


		if (seatsAvailable < 1)
		{
			std::cout << "\n\nThere are currently no available seats... " << std::endl;
			return;
		}

		else
		{
			while (choice != "Y" && choice != "y" && choice != "N" && choice != "n")
			{
				std::cin.clear(); // clear input error
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
				std::cout << "\nDo you wish to purchase seat tickets? Y/N: ";
				std::cin >> choice;
			}
		}

		if (choice == "Y" || choice == "y")
		{
			if (isManager) //if user is a manager then ask if they wish to add a discount to the purchase
			{
				ticketsClass.setDiscountPercentage();
			}

			totalCost = 0; //reset

			while (true)
			{
				
				do
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "\nPlease enter how many seats/tickets you wish to purchase (Maximum is 4): ";
					std::cin >> seatAmount;
					
					if (seatsAvailable == 0)
					{
						std::cout << "There are currently no seats available..." << std::endl;
						break;
					}
					
					else if (seatAmount > seatsAvailable && seatsAvailable > 0)
					{
						std::cout << "\n\nThe amount of seats you have selected currently exceeds the number of available seats... \n" << std::endl;
						std::cout << "\nNumber of seats available: " << seatsAvailable << std::endl;
					}


				} while (seatAmount < 1 || seatAmount > 4 || std::cin.fail() || seatAmount > seatsAvailable);


				if (seatAmount >= 1 && seatAmount <= 4 && seatAmount <= seatsAvailable)
				{
					break;
				}
			}


			std::cout << "\n\nBase Ticket Price: " << "\x9c" <<
							"10.00\nRow 1 and 2 will cost an extra " << "\x9c" <<
								"15 per ticket. Rows 3 to 5 will cost an extra " << "\x9c" << 
									"7.50 per ticket.\n\n"; //ticket price per row

			for (int i = 0; i < seatAmount; i++) //do for number of seats user wishes to purchase
			{
				do
				{
					do
					{
						std::cin.clear(); //clears input error
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Please select the ROW you wish to purchase ticket " << seatCounter << " from: ";
						std::cin >> rowChosen;
					} while (std::cin.fail() || rowChosen < 1 || rowChosen > rows);
					rowCheck = rowChosen - 1; //gets correct index since it starts from 0
					std::cout << std::endl;

					do
					{
						std::cin.clear(); //clears input error
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Please select the COLUMN you wish to purchase ticket " << seatCounter << " from: ";
						std::cin >> columnChosen;
					} while (std::cin.fail() || columnChosen < 1 || columnChosen > columns);
					columnCheck = columnChosen - 1; //gets correct index since it starts from 0

					if (seatPlan[rowCheck][columnCheck] != 'A')
					{
						system("cls");
						displaySeats();
						std::cout << "\n\nThat seat is currently unavaiable, please choose another: \n\n";
					}
				} while (seatPlan[rowCheck][columnCheck] != 'A');

				seatCounter++;
				seatPlan[rowCheck][columnCheck] = 'H'; //sets chosen seats to H (holding)
				
				ticketsClass.calculateCost(rowChosen, seatCounter);
				displaySeats();
				std::cout << std::endl << std::endl;
			}

			purchaseConfirmed = ticketsClass.purchaseReceipt(userClass); //FRIENDSHIP
	
			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					if (purchaseConfirmed == true) //if purchase confirmed then seats are now taken
					{
						if (seatPlan[r][c] == 'H')
						{
							seatPlan[r][c] = 'T';
						}
					}

					else if (purchaseConfirmed == false) //if purchase cancelled then seats available again
					{
						if (seatPlan[r][c] == 'H')
						{
							seatPlan[r][c] = 'A';
						}
					}

					else
					{
						seatPlan[r][c] = 'A';
					}
				}
			}
		}

		else if (choice == "N" || choice == "n") //if N purchase ticket then go to main menu
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			exitChoice = true;
			break;
		}
		break;
	}
}