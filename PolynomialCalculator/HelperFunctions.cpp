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

			std::cout << "Invalid command! Please enter an option from 1 to 11!" << std::endl;
		}

		std::cout << "Enter your option here>> ";

		isInvalid = true;
	} while (!(std::cin >> option) || !isValidOption(option));

	return option;
}

bool isValidOption(uint32_t option) {
	return option >= OPTIONS_LOWER_BOUND && option <= OPTION_UPPER_BOUND;
}

int getDegree() {
	char degree[MAX_COEFFICIENT_LENGTH];
	bool isInvalid = false;

	do {
		if (isInvalid) {
			std::cin.clear();

			std::cin.ignore(128, '\n');

			std::cout << "Invalid degree! Please enter a number greater or equal to 1!" << std::endl;
		}

		std::cout << "Enter the degree of your polynomial>> ";

		isInvalid = true;
	} while (!(std::cin >> degree) || !isValidDegree(degree));

	return (myAtoi(degree));
}

bool isValidDegree(const char* degree) {
	if (containsSymbols(degree)) {
		return false;
	}
	int splitIdx = find(degree, '/');
	if (splitIdx == -1) {
		int num = myAtoi(degree);
		if (num >= 1) {
			return true;
		}
	}
	return false;
}

bool containsSymbols(const char* str) {
	while (*str) {
		if (!((*str >= '0' && *str <= '9') || (*str == '/'))) {
			return true;
		}
		str++;
	}
	return false;
}

void getCoefficient(char* coefficient, int currentDegree) {
	bool isInvalid = false;

	do {
		if (isInvalid) {
			std::cin.clear();

			std::cin.ignore(128, '\n');

			std::cout << "Invalid coefficient! Please enter a non-zero denominator!" << std::endl;
		}

		std::cout << "Enter coefficient before x^" << currentDegree << ">> ";

		isInvalid = true;
	} while (!(std::cin >> coefficient) || !isValidCoefficient(coefficient));
}

bool isValidCoefficient(const char* str) {

	int strLength = myStrlen(str);

	if (strLength == 0) {
		return false;
	}

	int indexOfSplitter = find(str, '/');

	if (indexOfSplitter == -1) {
		return true;
	}

	char* denominatorSubstr = substring(str, 0, strLength);
	int denominator = myAtoi(denominatorSubstr);

	delete[] denominatorSubstr;

	if (denominator == 0) {
		return false;
	}

	return true;
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
	char* substr = new char[endIdx - startIdx + 1];
	int currIdx = startIdx;
	while (currIdx < endIdx) {
		*substr = str[currIdx];
		substr++;
		currIdx++;
	}
	*substr = '\0';
	substr -= (endIdx - startIdx);
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
	int gcd = GCD(myAbs(r.first), myAbs(r.second));
	r.first /= gcd;
	r.second /= gcd;
	if (r.second < 0) {
		r.first = -r.first;
		r.second = -r.second;
	}
	return r;
}

Rational addRational(Rational a, Rational b) {
	if (a.first == 0) {
		return reduce(b);
	}
	if (b.first == 0) {
		return reduce(a);
	}
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
		bool isNegative = false;
		if (contains(str, '-')) {
			isNegative = true;
			str++;
		}
		int numerator = myAtoi(str);
		if (isNegative) {
			numerator *= -1;
		}
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
	int degree = getDegree();

	Polynomial polynomial(degree + 1);
	for (int i = 0; i <= degree; i++) {
		int currentDegree = degree - i;
		char coefficient[MAX_COEFFICIENT_LENGTH];
		getCoefficient(coefficient, currentDegree);
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
	bool hasZerosOnly = true;
	for (int i = 0; i <= maxDegree; i++) {
		if (polynomial[i].first != 0) {

			hasZerosOnly = false;

			std::cout << (isPositive(polynomial[i]) && (maxDegree - i) != maxDegree ? "+" : "");

			if (polynomial[i].second == 1) {
				if (i != maxDegree && polynomial[i].first == -1) {
					std::cout << "-";
				}
				else if (polynomial[i].first == -1) {
					std::cout << polynomial[i].first;
				}
				else if (polynomial[i].first != 1 || i == maxDegree) {
					std::cout << polynomial[i].first;
				}
			}
			else {
				std::cout << polynomial[i].first << "/" << polynomial[i].second;
			}

			if (i < maxDegree - 1) {
				std::cout << "x^" << (maxDegree - i);
			}
			else if (i == maxDegree - 1) {
				std::cout << "x";
			}
			
		}
	}

	if (hasZerosOnly) {
		std::cout << "0";
	}

	std::cout << std::endl << std::endl;
}

Polynomial add(Polynomial Px, Polynomial Qx) {
	int PxSize = Px.size();
	int QxSize = Qx.size();

	int size = getMax(PxSize, QxSize);

	Polynomial result(size);

	int firstIdx = 0;
	int secondIdx = 0;

	for (int i = 0; i < size; i++) {

		Rational firstTerm = (size - i) <= PxSize ? Px[firstIdx++] : Rational{ 0,1 };
		Rational secondTerm = (size - i) <= QxSize ? Qx[secondIdx++] : Rational{ 0,1 };

		result[i] = addRational(firstTerm, secondTerm);
	}
	return result;
}

int getMax(int a, int b) {
	return (a >= b ? a : b);
}

int getMin(int a, int b) {
	return (a < b ? a : b);
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

Polynomial multiply(Polynomial Px, Polynomial Qx) {
	int PxSize = Px.size();
	int QxSize = Qx.size();

	int size = PxSize + QxSize - 1;
	Polynomial result(size);

	for (int i = 0; i < PxSize; i++) {
		for (int j = 0; j < QxSize; j++) {

			Rational currentProduct = multiplyRational(Px[i], Qx[j]);

			result[i + j] = addRational(result[i + j], currentProduct);

		}
	}

	return result;
}

void divide(Polynomial Ax, Polynomial Bx) {
	int AxSize = Ax.size();
	int BxSize = Bx.size();

	if (AxSize < BxSize) {
		std::cout << "The degree of the dividend must be greater or equal to the degree of the divisor!" << std::endl;
		return;
	}

	Polynomial quotient(AxSize - BxSize + 1);

	int quotientIdx = 0;

	while (AxSize >= BxSize) {

		int currentDegree = AxSize - BxSize;

		Rational reciprocal = { Bx[LEADIND_COEFFICIENT_IDX].second, Bx[LEADIND_COEFFICIENT_IDX].first };
		Rational currentCoefficient = multiplyRational(Ax[LEADIND_COEFFICIENT_IDX], reciprocal);

		quotient[quotientIdx++] = currentCoefficient;

		Polynomial currentQuotient(currentDegree + 1);
		currentQuotient[LEADIND_COEFFICIENT_IDX] = currentCoefficient;

		Polynomial currentProduct = multiply(Bx, currentQuotient);

		Ax = add(Ax, multiplyPolynomialByMinusOne(currentProduct));
		Ax.erase(Ax.begin());

		AxSize--;
	}

	std::cout << "Quotient Q(x)=";
	printPolynomial(quotient);

	std::cout << "Remainder R(x)=";
	printPolynomial(Ax);
}