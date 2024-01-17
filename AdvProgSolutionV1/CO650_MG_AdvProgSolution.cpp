#include <iostream> //inputs/outputs
#include <iomanip>

#include <stdlib.h> //standard library 

#include <windows.h> //for altering console window properties

#include "User.h"
#include "Menu.h"

menu menuClass; //[a form of CONSTRUCTORS - calls constructor of new class object]


int main()
{
	HWND console = GetConsoleWindow(); //built-in (windows.h) function to grab the console
	RECT rectangle; //built-in struct for console window


	GetWindowRect(console, &rectangle); //matches console data from GetConsoleWindow with RECT structure so MoveWindow() will work
	MoveWindow(console, rectangle.left, rectangle.top, 1600, 900, TRUE); //resizes console using RECT (rectangle) structure at 1600x900 and refreshes window

	menuClass.accountScreen(); //start ticket machine
	return 0;
}