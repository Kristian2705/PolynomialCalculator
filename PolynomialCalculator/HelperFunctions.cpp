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

int GCD(int a, int b) {
	while (a != b) {
		if (a > b) {
			a -= b;
		}
		else {
			b -= a;
		}
	}
	return a;
}

bool contains(const char* str, char symbol) {
	if (!str) {
		return false;
	}
	while (*str)
	{
		if (*str == symbol) {
			return true;
		}
		str++;
	}
	return false;
}

int find(const char* str, char symbol) {
	if (!str) {
		return -1;
	}
	int index = 0;
	while (*str)
	{
		if (*str == symbol) {
			return index;
		}
		str++;
		index++;
	}
	return -1;
}

char* substring(const char* str, int startIdx, int endIdx) {
	char* substr = new char[endIdx - startIdx];
	int currIdx = startIdx;
	while (currIdx < endIdx) {
		*substr = str[currIdx];
		substr++;
		currIdx++;
	}
	substr-= (endIdx - startIdx);
	return substr;
}

unsigned int myAtoi(const char* str) {
	int res = 0;
	int multiplier = 1;
	int length = myStrlen(str);
	str += length;
	str--;
	while (length > 0) {
		if (*str < '0' || *str > '9') {
			break;
		}
		int digit = *str - '0';
		if (digit == 0) {
			str--;
			res *= 10;
			length--;
			continue;
		}
		res += digit * multiplier;
		multiplier *= 10;
		str--;
		length--;
	}
	return res;
}

unsigned int myStrlen(const char* str) {
	int counter = 0;
	while (*str) {
		if ((*str >= '0' && *str <= '9') || *str == '/') {
			counter++;
		}
		str++;
	}
	return counter;
}

Rational reduce(Rational r) {
	int g = GCD(r.first, r.second);
	r.first /= g;
	r.second /= g;
	if (r.second < 0) {
		r.first = -r.first;
		r.second = -r.second;
	}
	return r;
}

Rational addRational(Rational a, Rational b) {
	int numerator = a.first * b.second + b.first * a.second;
	int denominator = a.second * b.second;
	return reduce({ numerator, denominator });
}

Rational subtractRational(Rational a, Rational b) {
	int numerator = a.first * b.second - b.first * a.second;
	int denominator = a.second * b.second;
	return reduce({ numerator, denominator });
}

Rational multiplyRational(Rational a, Rational b) {
	int numerator = a.first * b.first;
	int denominator = a.second * b.second;
	return reduce({ numerator, denominator });
}

Rational parseCoefficient(const char* str) {
	int indexOfSplitter = find(str, '/');
	if (indexOfSplitter == -1) {
		int numerator = *str - '0';
		return { numerator, 1 };
	}
	char* numeratorSubstr = substring(str, 0, indexOfSplitter);
	int numerator = myAtoi(numeratorSubstr);

	delete[] numeratorSubstr;

	int strLength = myStrlen(str);

	char* denominatorSubstr = substring(str, indexOfSplitter + 1, strLength);
	int denominator = myAtoi(denominatorSubstr);

	delete[] denominatorSubstr;

	return reduce({ numerator, denominator });
}

void printPolynomial(std::vector<int>& polynomial, int degree) {
	for (int i = 0; i <= degree; i++) {
		int currentDegree = degree - i;
		int currentCoefficient = polynomial.at(i);
		if (currentCoefficient == 0) {
			continue;
		}
		if (currentDegree == degree) {
			if (currentCoefficient == 1 || currentCoefficient == -1) {
				std::cout << "x^" << currentDegree;
			}
			else {
				std::cout << currentCoefficient << "x^" << currentDegree;
			}
		}
		else if (currentDegree > 1) {
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

Polynomial enterPolynomial() {
	int degree = 0;
	std::cout << "Enter the degree of your polynomial>> ";
	std::cin >> degree;
	std::cin.ignore();

	Polynomial poly(degree + 1);
	for (int i = 0; i <= degree; i++) {
		char coefficient[10];
		int currentDegree = degree - i;
		std::cout << "Enter coefficient before x^" << currentDegree << ">> ";
		std::cin >> coefficient;
		poly[i] = parseCoefficient(coefficient);
	}
	return poly;
}