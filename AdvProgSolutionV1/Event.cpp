
#include "Event.h"


void event::displayEvents() //displays all the event details in a list 
{
	int eventNum = 0; //used to add a number to each of the lists printed below

	std::cout << "\nEvent Features: \n";
	for (const auto& name : eventNames)
	{
		eventNum++; //increments through each index in array for list
		std::cout << eventNum << "|\t" << name << std::endl;
	}

	eventNum = 0; //resets to 0 so can be incremented again

	std::cout << "\nEvent Dates: \n";
	for (const auto& date : eventDates)
	{
		eventNum++;
		std::cout << eventNum << "|\t" << date << std::endl;
	}

	eventNum = 0;

	std::cout << "\nEvent Times: \n";
	for (const auto& time : eventTimes)
	{
		eventNum++;
		std::cout << eventNum << "|\t" << time << std::endl;
	}

	chooseEvent = 0; //resets chooseEvent so that it is not being reused

	while (chooseEvent < 1 || chooseEvent > 4) 
	{

		std::cout << "\nPlease choose an event 1-4: ";
		std::cin >> chooseEvent;

		if (chooseEvent >= 1 && chooseEvent <= 4)
		{
			chooseEvent -= 1; //correct index for chosen event
			eventChoice();
			chooseEvent = 0; //reset
			return;
		}

		else
		{
			std::cin.clear(); //clears input error
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears input from stream so can be reinput  (used for cin.fail())
		}
	}
	return;
}


void event::eventChoice() //displays details for chosen event (index) in certain order to form a sentence
{
	system("cls");
	std::cout << "\nEvent " << chooseEvent + 1 << " features " << eventNames[chooseEvent] <<
		" on " << eventDates[chooseEvent] << " between " << (eventTimes[chooseEvent].substr(0, 5)) <<
		" and " << (eventTimes[chooseEvent].substr(eventTimes[chooseEvent].length() - 5)) << "." << std::endl;

	std::cout << "\nHere is the seating plan: \n\n";

	eventSeatClass.seatingPlan(); //a function in eventSeat.h that handles all of the seat arrangements
}