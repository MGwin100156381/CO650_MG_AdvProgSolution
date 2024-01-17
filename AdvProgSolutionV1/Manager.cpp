
#include "Manager.h"


void manager::displayProfile(tickets& ticketsClassObject) //ABSTRACTION displays manager account details (not standard user)
{
    std::cout << "\n\t\033[1;37mMANAGER PROFILE:\033[0m\n\n\tFirst Name:       " << managerFirstNames[userEmailIndex];
    std::cout << "\n\tSurname:          " << managerLastNames[userEmailIndex];
    std::cout << "\n\tAddress:          " << managerAddresses[userEmailIndex];
    std::cout << "\n\tDate of Birth:\t  " << managerDOBs[userEmailIndex] << std::endl;
    ticketsClassObject.displayTickets();


    std::cout << "\n\n\n\t\t\033[1;37m1: Edit Profile\n";
    std::cout << "\t\t2: Refund Ticket\n";
    std::cout << "\t\t3: Main Menu\n\033[0m";
    std::cout << "\n\nPlease choose from one of these menu options: ";


    int profileChoice = 0;
    std::cin >> profileChoice;
    while (std::cin.fail() || profileChoice < 1 || profileChoice > 3)
    {
        std::cin.clear(); //clear input error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input buffer
        std::cout << "Please choose from the options stated: ";
        std::cin >> profileChoice;
    }


    switch (profileChoice)
    {
    case 1: //sets the manager profile details
        setProfile(isManager);
        break;


    case 2: //refund chosen purchased tickets

        if (size(ticketsClassObject.userTickets) < 1) //if user has no tickets then cancel
        {
            system("cls"); //clears screen
            std::cout << "\nYou do not currently have any tickets to refund..." << std::endl;
            displayProfile(ticketsClassObject);
        }

        else //allow manager to refund ticket
        {
            ticketsClassObject.refundTicket();
            displayProfile(ticketsClassObject);
        }

        break;


    case 3: //back to main menu
        system("cls");
        break;


    default:
        std::cout << "Please choose from the options stated: ";
        std::cin.get();
    }
}


void manager::ticketMachineConfiguration() //manager can configure certain ticket machine elements such as deleting user accounts
{
    int configChoice = 0;

    std::cout << "1: View User Accounts" << std::endl;
    std::cout << "2: View Manager Accounts" << std::endl;
    std::cout << "3: View Events" << std::endl;
    std::cout << "4: Main Menu" << std::endl;


    std::cout << "\n\nPlease choose from one of these menu options: ";

    std::cin >> configChoice;
    while (std::cin.fail() || configChoice < 1 || configChoice > 4)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please choose from the options stated: ";
        std::cin >> configChoice;
    }


    switch (configChoice)
    {
    case 1: //view standard user accounts and ask whether manager wants to delete a chosen account
        viewUserAccounts();
        deleteConsumerAccount();
        break;

    case 2: //view manager user accounts asks whether manager wants to delete a manager account
        viewManagerAccounts();
        deleteManagerAccount();
        break;


    case 3: //displays current events
        //addManager();
        eventClass.displayEvents();
        break;


    case 4:
        system("cls");
        break;


    default:
        std::cout << "Please choose from the options stated: ";
        std::cin.get();
    }
}


void manager::viewUserAccounts() //allows manager to view standard user accounts
{
    int counter = 1;
    userIndex = 0;

    for (const auto& name : consumerFirstNames) //displays first name of each standard user account
    {
        std::cout << "\nUser " << counter << ":\t" << name;
        counter++;
    }

    std::cout << "\n\n\nPlease choose the user account you wish to view (1 - " << (counter - 1) << "): ";
    std::cin >> userIndex;
    userIndex -= 1; //correct user index
    std::cout << std::endl;
    
    //POINTERS accesses standard user account details through pointers so values are not mistakenly changed
    const std::string* firstName = &(consumerFirstNames[userIndex]);
    const std::string* lastName = &(consumerLastNames[userIndex]);
    const std::string* address = &(consumerAddresses[userIndex]);
    const std::string* dob = &(consumerDOBs[userIndex]);
    const int* age = &(consumerAges[userIndex]);

    //POINTERS displays standard user account details via pointers
    std::cout << "\n\t\033[1;37mPROFILE:\033[0m\n\n\tFirst Name:       " << *firstName; 
    std::cout << "\n\tSurname:          " << *lastName;
    std::cout << "\n\tAddress:          " << *address;
    std::cout << "\n\tDate of Birth:\t  " << *dob;
    std::cout << "\n\tUser Age:         " << *age << std::endl;
}


void manager::viewManagerAccounts() //allows manager to view manager user accounts
{
    int counter = 1;
    userIndex = 0;

    for (const auto& name : managerFirstNames)
    {
        std::cout << "\nManager " << counter << ":\t" << name;
        counter++;
    }

    std::cout << "\n\n\nPlease choose the user account you wish to view (1 - " << (counter - 1) << "): ";
    std::cin >> userIndex;
    userIndex -= 1;

    std::cout << std::endl;
    std::cout << "\n\t\033[1;37mPROFILE:\033[0m\n\n\tFirst Name:       " << managerFirstNames[userIndex];
    std::cout << "\n\tSurname:          " << managerLastNames[userIndex];
    std::cout << "\n\tAddress:          " << managerAddresses[userIndex];
    std::cout << "\n\tDate of Birth:\t  " << managerDOBs[userIndex];
    std::cout << "\n\tUser Age:         " << managerAges[userIndex] << std::endl;
}



void manager::deleteConsumerAccount() //allows manager to delete standard user account
{
    std::string deleteChoice;

    std::cout << std::endl;
    while (deleteChoice != "Y" && deleteChoice != "y" && deleteChoice != "N" && deleteChoice != "n")
    {
        std::cin.clear(); // clear input error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        std::cout << "\nDo you wish to delete this account? Y/N: ";
        std::cin >> deleteChoice;
    }

    if (deleteChoice == "Y" || deleteChoice == "y") 
    {
        system("cls");
        std::cout << "\033[32m\n\n\tUser " << (userIndex + 1) << " '" << consumerFirstNames[userIndex] << " " << consumerLastNames[userIndex] << "' has been deleted\033[0m" << std::endl;

        consumerFirstNames.erase(consumerFirstNames.begin() + userIndex);
        consumerLastNames.erase(consumerLastNames.begin() + userIndex);
        consumerAddresses.erase(consumerAddresses.begin() + userIndex);
        consumerDOBs.erase(consumerDOBs.begin() + userIndex);
        consumerAges.erase(consumerAges.begin() + userIndex);
    }

}


void manager::deleteManagerAccount() //allows manager to delete other manager user accounts
{
    std::string deleteChoice;

    std::cout << std::endl;
    while (deleteChoice != "Y" && deleteChoice != "y" && deleteChoice != "N" && deleteChoice != "n")
    {
        std::cin.clear(); // clear input error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        std::cout << "\nDo you wish to delete this account? Y/N: ";
        std::cin >> deleteChoice;
    }

    if (deleteChoice == "Y" || deleteChoice == "y")
    {
        system("cls");
        std::cout << "\033[32m\n\n\tUser " << (userIndex + 1) << " '" << managerFirstNames[userIndex] << " " << managerLastNames[userIndex] << "' has been deleted\033[0m" << std::endl;

        managerFirstNames.erase(managerFirstNames.begin() + userIndex);
        managerLastNames.erase(managerLastNames.begin() + userIndex);
        managerAddresses.erase(managerAddresses.begin() + userIndex);
        managerDOBs.erase(managerDOBs.begin() + userIndex);
        managerAges.erase(managerAges.begin() + userIndex);
    }

}


void manager::addManager() //allows manager to add other manager accounts
{
    std::string newEmail;
    std::string newPassword;
    bool emailAt, emailDot, emailExists; //email formatting (must include "@" and ".")
    std::string confirmAccount;

    std::cout << std::endl;
    while (true)
    {
        do //validates that new email includes "@" and "." and is nit already registered
        {
            emailAt = false;
            emailDot = false;
            emailExists = false;
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter a new manager email: ";
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
        } while (std::cin.fail() || (emailAt != true || emailDot != true) || emailExists == true);

        std::cout << std::endl;

        do
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Please enter a new manager password: ";
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
        system("cls"); //clears screen
        std::cout << std::endl;
    }
}