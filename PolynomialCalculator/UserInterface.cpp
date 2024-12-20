/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Kristian Petrov
* @idnumber 3MI0600416
* @compiler VCC
*
*/

#include "UserInterface.h";
#include "HelperFunctions.h";

void polynomialCalculator() {

	bool exitCommand = false;

	std::cout << 
		"Welcome to Polynomial Calculator - a mini project intended to work with polynomials with rational coefficients" 
		<< std::endl;
	std::cout << "Choose one of the following functionalities:" << std::endl;
	std::cout << "1) Add polynomials" << std::endl;
	std::cout << "2) Subtract polynomials" << std::endl;
	std::cout << "3) Multiply polynomials" << std::endl;
	std::cout << "4) Divide polynomials" << std::endl;
	std::cout << "5) Multiply polynomial by scalar" << std::endl;
	std::cout << "6) Find value of polynomial at a given number" << std::endl;
	std::cout << "7) Find GCD of two polynomials" << std::endl;
	std::cout << "8) Display Vieta's formulas for a given polynomial" << std::endl;
	std::cout << "9) Represent a polynomial in powers of (x+a)" << std::endl;
	std::cout << "10) Factor polynomial and find its rational roots" << std::endl;
	std::cout << "11) Quit program" << std::endl;
	std::cout << std::endl;

	do {
		uint32_t menuOption = getOption();
		switch (menuOption)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				std::cout << "You have successfully exited the program!" << std::endl;
				exitCommand = true;
				break;
			default:
				break;
		}
	} while (!exitCommand);
}