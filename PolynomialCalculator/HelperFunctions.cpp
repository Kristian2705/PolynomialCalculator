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
	bool isNegative = contains(str, '-');
	str += length;
	str--;
	while (length > 0) {
		if (*str < '0' || *str > '9') {
			break;
		}
		int digit = *str - '0';
		if (digit == 0) {
			str--;
			multiplier *= 10;
			length--;
			continue;
		}
		res += digit * multiplier;
		multiplier *= 10;
		str--;
		length--;
	}
	if (isNegative) {
		res *= -1;
		str--;
	}
	return res;
}

unsigned int myStrlen(const char* str) {
	int counter = 0;
	while (*str) {
		if ((*str >= '0' && *str <= '9') || *str == '/' || *str == '-') {
			counter++;
		}
		str++;
	}
	return counter;
}

unsigned int myAbs(int num) {
	return (num > 0 ? num : -num);
}

Rational reduce(Rational r) {
	if (r.first == 0) {
		return r;
	}
	int g = GCD(myAbs(r.first), myAbs(r.second));
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

Polynomial enterPolynomial() {
	int degree = 0;
	std::cout << "Enter the degree of your polynomial>> ";
	std::cin >> degree;
	std::cin.ignore();

	Polynomial polynomial(degree + 1);
	for (int i = 0; i <= degree; i++) {
		char coefficient[MAX_COEFFICIENT_LENGTH];
		int currentDegree = degree - i;
		std::cout << "Enter coefficient before x^" << currentDegree << ">> ";
		std::cin >> coefficient;
		polynomial[i] = parseCoefficient(coefficient);
	}
	return polynomial;
}

bool isEqualToOne(Rational coefficient) {
	return (coefficient.first == 1 && coefficient.second == 1);
}

bool isEqualToMinusOne(Rational coefficient) {
	return (coefficient.first == -1 && coefficient.second == 1);
}

bool isPositive(Rational coefficient) {
	return (coefficient.first > 0 && coefficient.second > 0);
}


//IMPORTANT: it may be needed to add a case for degree 0

void printPolynomial(Polynomial polynomial) {
	int maxDegree = polynomial.size() - 1;
	for (int i = 0; i <= maxDegree; i++) {
		int currentDegree = maxDegree - i;
		Rational currentCoefficient = polynomial.at(i);
		if (currentCoefficient.first == 0) {
			continue;
		}
		if (currentDegree == maxDegree) {
			if (maxDegree == 1) {
				if (isEqualToOne(currentCoefficient) || isEqualToMinusOne(currentCoefficient)) {
					std::cout << "x^" << currentDegree;
				}
				else if (currentCoefficient.second == 1) {
					std::cout << currentCoefficient.first << "x";
				}
				else {
					std::cout << currentCoefficient.first << "/" << currentCoefficient.second << "x";
				}
			}
			else {
				if (isEqualToOne(currentCoefficient) || isEqualToMinusOne(currentCoefficient)) {
					std::cout << "x^" << currentDegree;
				}
				else if (currentCoefficient.second == 1) {
					std::cout << currentCoefficient.first << "x^" << currentDegree;
				}
				else {
					std::cout << currentCoefficient.first << "/" << currentCoefficient.second << "x^" << currentDegree;
				}
			}
		}
		else if (currentDegree > 1) {
			if (isPositive(currentCoefficient)) {
				if (isEqualToOne(currentCoefficient)) {
					std::cout << "+x^" << currentDegree;
				}
				else if (currentCoefficient.second == 1) {
					std::cout << "+" << currentCoefficient.first << "x^" << currentDegree;
				}
				else {
					std::cout << "+" << currentCoefficient.first << "/" << currentCoefficient.second << "x^" << currentDegree;
				}
			}
			else {
				if (isEqualToMinusOne(currentCoefficient)) {
					std::cout << "-x^" << currentDegree;
				}
				else if (currentCoefficient.second == 1) {
					std::cout << currentCoefficient.first << "x^" << currentDegree;
				}
				else {
					std::cout << currentCoefficient.first << "/" << currentCoefficient.second << "x^" << currentDegree;
				}
			}
		}
		else if (currentDegree == 1) {
			if (isPositive(currentCoefficient)) {
				if (isEqualToOne(currentCoefficient)) {
					std::cout << "+x";
				}
				else if(currentCoefficient.second == 1){
					std::cout << "+" << currentCoefficient.first << "x";
				}
				else {
					std::cout << "+" << currentCoefficient.first << "/" << currentCoefficient.second << "x";
				}
			}
			else {
				if (isEqualToMinusOne(currentCoefficient)) {
					std::cout << "-x";
				}
				else if (currentCoefficient.second == 1) {
					std::cout << currentCoefficient.first << "x";
				}
				else {
					std::cout << currentCoefficient.first << "/" << currentCoefficient.second << "x";
				}
			}
		}
		else {
			if (isPositive(currentCoefficient)) {
				if (currentCoefficient.second == 1) {
					std::cout << "+" << currentCoefficient.first << std::endl;
				}
				else {
					std::cout << "+" << currentCoefficient.first << "/" << currentCoefficient.second << std::endl;
				}
			}
			else {
				if (currentCoefficient.second == 1) {
					std::cout << currentCoefficient.first << std::endl;
				}
				else {
					std::cout << currentCoefficient.first << "/" << currentCoefficient.second << std::endl;
				}
			}
		}
	}
	std::cout << std::endl;
}

Polynomial add(Polynomial Px, Polynomial Qx) {
	int PxSize = Px.size();
	int QxSize = Qx.size();

	int size = getMax(PxSize, QxSize);

	Polynomial result(size);

	int minSize = getMin(PxSize, QxSize);

	int firstIdx = 0;
	int secondIdx = 0;

	for (int i = 0; i < size; i++) {

		Rational firstTerm = (minSize - i) < PxSize ? Px[firstIdx++] : Rational{ 0,1 };
		Rational secondTerm = (minSize - i) < QxSize ? Qx[secondIdx++] : Rational{ 0,1 };

		result[i] = addRational(firstTerm, secondTerm);
	}
	return result;
}

Polynomial multiplyPolynomialByMinusOne(Polynomial Qx) {
	int size = Qx.size();
	for (int i = 0; i < size; i++) {
		if (Qx[i].first == 0) {
			continue;
		}
		Qx[i] = { -Qx[i].first, Qx[i].second };
	}
	return Qx;
}

int getMax(int a, int b) {
	return (a >= b ? a : b);
}

int getMin(int a, int b) {
	return (a < b ? a : b);
}