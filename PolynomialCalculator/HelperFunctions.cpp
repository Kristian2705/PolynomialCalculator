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

#include "HelperFunctions.h"
#include "Constants.h"

uint32_t getOption() {
	uint32_t option = 0;
	bool isInvalid = false;

	do {
		if (isInvalid) {
			std::cin.clear();

			std::cin.ignore(128, '\n');

			std::cout << "Invalid command! Please enter an option from 1 to 11" << std::endl;
		}

		std::cout << "Enter your option here>> ";

		isInvalid = true;
	} while (!(std::cin >> option) || !isValidOption(option));

	return option;
}

bool isValidOption(uint32_t option) {
	return option >= OPTIONS_LOWER_BOUND && option <= OPTION_UPPER_BOUND;
}

void printPolynomial(std::vector<int>& polynomial, int degree) {
	for (int i = 0; i <= degree; i++) {
		int currentDegree = degree - i;
		if (currentDegree == degree) {
			int currentCoefficient = polynomial.at(i);
			if (currentCoefficient == 1 || currentCoefficient == -1) {
				std::cout << "x^" << currentDegree;
			}
			else {
				std::cout << currentCoefficient << "x^" << currentDegree;
			}
		}
		else if (currentDegree > 1) {
			int currentCoefficient = polynomial.at(i);
			if (currentCoefficient > 0) {
				if (currentCoefficient == 1) {
					std::cout << "+x^" << currentDegree;
				}
				else {
					std::cout << "+" << currentCoefficient << "x^" << currentDegree;
				}
			}
			else {
				if (currentCoefficient == -1) {
					std::cout << "-x^" << currentDegree;
				}
				else {
					std::cout << currentCoefficient << "x^" << currentDegree;
				}
			}
		}
		else if (currentDegree == 1) {
			int currentCoefficient = polynomial.at(i);
			if (currentCoefficient > 0) {
				if (currentCoefficient == 1) {
					std::cout << "+x";
				}
				else {
					std::cout << "+" << currentCoefficient << "x";
				}
			}
			else {
				if (currentCoefficient == -1) {
					std::cout << "-x";
				}
				else {
					std::cout << currentCoefficient << "x";
				}
			}
		}
		else {
			int currentCoefficient = polynomial.at(i);
			if (currentCoefficient > 0) {
				std::cout << "+" << currentCoefficient << std::endl;
			}
			else {
				std::cout << currentCoefficient << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void enterPolynomial(std::vector<int>& polynomial, int& degree) {
	std::cout << "Enter degree of your polynomial>> ";
	std::cin >> degree;
	for (int i = 0; i <= degree; i++) {
		int currentCoefficient = 0;
		std::cout << "Enter coefficient before x^" << degree - i << ">> ";
		std::cin >> currentCoefficient;
		polynomial.push_back(currentCoefficient);
	}
}