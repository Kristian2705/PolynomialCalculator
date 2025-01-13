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

int getOption() {
	char strOption[MAX_COEFFICIENT_LENGTH];
	bool isInvalid = false;

	do {
		if (isInvalid) {
			std::cin.clear();

			std::cin.ignore(128, '\n');

			std::cout << "Invalid command! Please enter an option from 1 to 11!" << std::endl;
		}

		std::cout << "Enter your option here>> ";

		isInvalid = true;
	} while (!(std::cin >> strOption) || !isValidInteger(strOption));

	return myAtoi(strOption);
}

bool isValidOption(int option) {
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
	} while (!(std::cin >> degree) || !isValidInteger(degree));

	return (myAtoi(degree));
}

bool isValidInteger(const char* integer) {
	if (containsSymbols(integer)) {
		return false;
	}
	int splitIdx = find(integer, '/');
	if (splitIdx == -1) {
		int num = myAtoi(integer);
		if (num >= 1) {
			return true;
		}
	}
	return false;
}

bool containsSymbols(const char* str) {
	while (*str) {
		if (!((*str >= '0' && *str <= '9') || (*str == '/') || (*str == '-'))) {
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

void getScalar(char* scalar) {
	bool isInvalid = false;

	do {
		if (isInvalid) {
			std::cin.clear();

			std::cin.ignore(128, '\n');

			std::cout << "Invalid rational number! Please enter a non-zero denominator!" << std::endl;
		}

		std::cout << "Enter rational number>> ";

		isInvalid = true;
	} while (!(std::cin >> scalar) || !isValidCoefficient(scalar));
}

bool isValidCoefficient(const char* str) {

	if (containsSymbols(str)) {
		return false;
	}

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
}

void printRational(Rational number) {
	if (number.second == 1) {
		std::cout << number.first;
	}
	else {
		std::cout << number.first << "/" << number.second;
	}
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

	trimPolynomial(Ax);

	std::cout << "Quotient Q(x)=";
	printPolynomial(quotient);
	std::cout << std::endl << std::endl;

	std::cout << "Remainder R(x)=";
	printPolynomial(Ax);
	std::cout << std::endl << std::endl;
}

void trimPolynomial(Polynomial& polynomial) {
	while (!polynomial.empty() && polynomial[LEADIND_COEFFICIENT_IDX].first == 0) {
		polynomial.erase(polynomial.begin());
	}
}

Polynomial getMultipliedPolynomialByScalar(Polynomial Px, Rational scalar) {
	int PxSize = Px.size();
	Polynomial result(PxSize);

	for (int i = 0; i < PxSize; i++) {
		result[i] = multiplyRational(Px[i], scalar);
	}

	return result;
}

Rational getPolynomialValue(Polynomial Px, Rational scalar) {
	int maxDegree = Px.size() - 1;

	Rational sum = { 0,1 };
	Rational multiplier = { 1, 1 };

	for (int i = maxDegree; i >= 0 ; i--) {
		Rational currentResult = multiplyRational(Px[i], multiplier);
		sum = addRational(sum, currentResult);
		multiplier = multiplyRational(multiplier, scalar);
	}

	return sum;
}

Polynomial getPolynomialRemainder(Polynomial Px, Polynomial Qx) {
	int PxSize = Px.size();
	int QxSize = Qx.size();

	while (PxSize >= QxSize) {

		int currentDegree = PxSize - QxSize;

		Rational reciprocal = { Qx[LEADIND_COEFFICIENT_IDX].second, Qx[LEADIND_COEFFICIENT_IDX].first };
		Rational currentCoefficient = multiplyRational(Px[LEADIND_COEFFICIENT_IDX], reciprocal);

		Polynomial currentQuotient(currentDegree + 1);
		currentQuotient[LEADIND_COEFFICIENT_IDX] = currentCoefficient;

		Polynomial currentProduct = multiply(Qx, currentQuotient);

		Px = add(Px, multiplyPolynomialByMinusOne(currentProduct));
		Px.erase(Px.begin());

		PxSize--;
	}

	trimPolynomial(Px);

	return Px;
}

Polynomial getGCD(Polynomial Px, Polynomial Qx) {
	if (Qx.empty()) {
		if (Px.size() == 1) {
			Px[LEADIND_COEFFICIENT_IDX] = { 1, 1 };
		}
		return Px;
	}

	if (Px.size() < Qx.size()) {
		return getGCD(Px, getPolynomialRemainder(Qx, Px));
	}

	return getGCD(Qx, getPolynomialRemainder(Px, Qx));
}

void printVietaFormulas(Polynomial Px) {
	Rational leadingCoefficient = Px[LEADIND_COEFFICIENT_IDX];

	int PxSize = Px.size();
	int multiplier = -1;

	int* numberOfRoots = new int[PxSize - 1];
	for (int i = 1; i <= PxSize - 1; i++) {
		numberOfRoots[i - 1] = i;
	}

	std::vector<std::vector<int>> subsets = getSubsets(numberOfRoots, PxSize - 1);
	subsets.erase(subsets.begin());

	for (int i = 1; i < PxSize; i++) {
		Rational currentResult = multiplyRational(Px[i], { leadingCoefficient.second * multiplier, leadingCoefficient.first });
		multiplier *= -1;
		printFormula(currentResult, i, PxSize - 1, subsets);
	}
}

void printFormula(Rational result, int idx, int maxRootNumber, std::vector<std::vector<int>>& subsets) {
	int maxTerms = getCombinations(maxRootNumber, idx);
	for (int i = 0; i < maxTerms; i++) {
		for (int j = 0; j < subsets[0].size(); j++) {
			std::cout << "x" << subsets[0][j];
		}
		subsets.erase(subsets.begin());
		if (i != maxTerms - 1) {
			std::cout << " + ";
		}
	}
	std::cout << " = ";
	printRational(result);
	std::cout << std::endl;
}

int getCombinations(int n, int k) {
	if (k == 0 || k == n) {
		return 1;
	}
	return getCombinations(n - 1, k - 1) + getCombinations(n - 1, k);
}

void printSubset(int arr[], int mask, int length, std::vector<int>& subest) {
	for (int i = 0; i < length; i++) {
		if (mask & 1) {
			subest.push_back(arr[i]);
		}
		mask >>= 1;
	}
}

bool compareSubsets(const std::vector<int>& a, const std::vector<int>& b) {
	int aSize = a.size();
	int bSize = b.size();
	if (aSize != bSize) {
		return aSize < bSize;
	}
	for (int i = 0; i < aSize && i < bSize; ++i) {
		if (a[i] != b[i]) {
			return a[i] < b[i];
		}
	}
	return false;
}

void manualSort(std::vector<std::vector<int>>& subsets) {
	int subsetsSize = subsets.size();
	for (int i = 0; i < subsetsSize; i++) {
		for (int j = i + 1; j < subsetsSize; j++) {
			if (!compareSubsets(subsets[i], subsets[j])) {
				swap(subsets[i], subsets[j]);
			}
		}
	}
}

std::vector<std::vector<int>> getSubsets(int arr[], int length) {
	int subestsCount = 1 << length;
	std::vector<std::vector<int>> subsets;
	for (int i = 0; i < subestsCount; i++) {
		std::vector<int> subset;
		printSubset(arr, i, length, subset);
		subsets.push_back(subset);
	}

	manualSort(subsets);

	return subsets;
}

Polynomial getPowers(Polynomial Px, Rational a) {
	Rational result = { 0, 1 };
	int PxSize = Px.size();

	Polynomial resultPolynomial(PxSize);

	Rational oppositeA = { -a.first, a.second };

	Polynomial currCoefficients = Px;

	for (int i = 0; i < PxSize - 1; i++) {

		int currCoefficientsSize = currCoefficients.size();

		for (int j = 0; j < currCoefficientsSize - 1; j++) {
			Rational currentCoefficient = currCoefficients[j];

			Rational currentResult = addRational(multiplyRational(currentCoefficient, { oppositeA.first, oppositeA.second }), currCoefficients[j + 1]);
			currCoefficients[j + 1] = currentResult;
		}

		resultPolynomial[PxSize - i - 1] = currCoefficients[currCoefficientsSize - 1];
		currCoefficients.pop_back();
	}

	resultPolynomial[LEADIND_COEFFICIENT_IDX] = currCoefficients[LEADIND_COEFFICIENT_IDX];

	return resultPolynomial;
}

void printAsPowers(Polynomial polynomial, Rational a, bool isPositiveA) {
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
				if (isPositiveA) {
					std::cout << "(x+";
				}
				printRational(a);
				std::cout << ")^" << (maxDegree - i);
			}
			else if (i == maxDegree - 1) {
				if (isPositiveA) {
					std::cout << "(x+";
				}
				printRational(a);
				std::cout << ")";
			}

		}
	}

	if (hasZerosOnly) {
		std::cout << "0";
	}

	std::cout << std::endl << std::endl;
}

void displayRootsAndFactors(Polynomial Px) {
	Rational constantTerm = Px.back();
	Rational leadingCoefficient = Px.front();

	int PxSize = Px.size();

	int allLCM = findLCMOfPolynomialCoefficients(Px);

	if (allLCM != 1) {
		turnPolynomialCoefficientsIntoIntegers(Px, allLCM, constantTerm, leadingCoefficient);
	}

	std::vector<Rational> possibleRoots;

	std::vector<Rational> pFactors = findFactors(constantTerm);
	std::vector<Rational> qFactors = findFactors(leadingCoefficient);

	getPossibleRoots(possibleRoots, pFactors, qFactors);

	std::vector<Rational> roots;

	getRoots(Px, roots, possibleRoots);

	int rootsCount = roots.size();
	
	if (rootsCount == 0) {
		printPolynomial(Px);
		std::cout << "=0";
		std::cout << std::endl << std::endl;
		std::cout << "There aren't any rational roots of Px" << std::endl;
		return;
	}

	std::vector<int> rootFolds(rootsCount);

	getRootFolds(Px, rootFolds, roots, rootsCount);

	factorizePolynomial(Px, roots, rootFolds);

	if (rootsCount > 0) {
		std::cout << "RATIONAL ROOTS:" << std::endl;
		for (int i = 0; i < rootsCount; i++) {
			std::cout << "x=";
			printRational(roots[i]);
			std::cout << " -> " << rootFolds[i] << "-fold root" << std::endl;
		}
	}
}

std::vector<Rational> findFactors(Rational num) {
	std::vector<Rational> factors;
	num = { abs(num.first), num.second };
	for (int i = 1; i <= sqrt(num.first); ++i) {
		if (num.first % i == 0) {
			factors.push_back({i, 1});
			factors.push_back({ -i, 1 });
			if (i != num.first / i) {
				factors.push_back({ num.first / i , 1 });
				factors.push_back({ -num.first / i, 1 });
			}
		}
	}
	return factors;
}

bool containsRoot(std::vector<Rational> possibleRoots, Rational num) {
	int size = possibleRoots.size();
	for (int i = 0; i < size; i++) {
		if (possibleRoots[i] == num) {
			return true;
		}
	}
	return false;
}

int findLCMOfPolynomialCoefficients(Polynomial Px) {
	int PxSize = Px.size();
	int lcm = Px[0].second;
	for (int i = 1; i < PxSize; i++) {
		lcm = ((Px[i].second * lcm) / GCD(lcm, Px[i].second));
	}
	return lcm;
}

void turnPolynomialCoefficientsIntoIntegers(Polynomial& Px, int lcm, Rational& constantTerm, Rational& leadingCoefficient){
	Rational gcdRational = { lcm, 1 };

	Px = getMultipliedPolynomialByScalar(Px, gcdRational);

	constantTerm = Px.back();
	leadingCoefficient = Px.front();
}

void getPossibleRoots(std::vector<Rational>& possibleRoots, const std::vector<Rational> pFactors, const std::vector<Rational> qFactors) {
	int pFactorsSize = pFactors.size();
	int qFactorsSize = qFactors.size();

	for (int i = 0; i < pFactorsSize; i++) {
		for (int j = 0; j < qFactorsSize; j++) {
			Rational possibleRoot;
			if (pFactors[i].first % qFactors[j].first == 0) {
				possibleRoot = { pFactors[i].first / qFactors[j].first, 1 };
			}
			else {
				possibleRoot = reduce({ pFactors[i].first, qFactors[j].first });
			}
			if (!containsRoot(possibleRoots, possibleRoot)) {
				possibleRoots.push_back(possibleRoot);
			}
		}
	}
}

void getRoots(Polynomial Px, std::vector<Rational>& roots, const std::vector<Rational> possibleRoots) {
	int possibleRootsCount = possibleRoots.size();

	for (int i = 0; i < possibleRootsCount; i++) {

		Rational currentRoot = possibleRoots[i];
		Rational result = getPolynomialValue(Px, currentRoot);

		if (result.first == 0) {
			roots.push_back(currentRoot);
		}
	}
}

void getRootFolds(Polynomial Px, std::vector<int>& rootFolds, std::vector<Rational> roots ,int rootsCount) {
	int rootCoefficient = 0;

	while (rootCoefficient < rootsCount) {

		int currCoefficientsSize = Px.size();

		Polynomial lastValidCoefficients = Px;

		for (int j = 0; j < currCoefficientsSize - 1; j++) {
			Rational currentCoefficient = Px[j];

			Rational currentResult = addRational(multiplyRational(currentCoefficient, roots[rootCoefficient]), Px[j + 1]);
			Px[j + 1] = currentResult;
		}

		if (Px[currCoefficientsSize - 1].first != 0) {
			rootCoefficient++;
			Px = lastValidCoefficients;
			continue;
		}

		rootFolds[rootCoefficient]++;
		Px.pop_back();
	}
}

void factorizePolynomial(Polynomial Px, std::vector<Rational> roots, std::vector<int> rootFolds) {
	int rootsCoefficient = 0;
	int currentRootFold = 1;

	int rootsSize = roots.size();
	int PxSize = Px.size();

	while (rootsCoefficient < rootsSize) {
		for (int i = 0; i < PxSize - 1; i++) {
			Rational currentCoefficient = Px[i];

			Rational currentResult = addRational(multiplyRational(currentCoefficient, roots[rootsCoefficient]), Px[i + 1]);
			Px[i + 1] = currentResult;
		}
		if (rootFolds[rootsCoefficient] == currentRootFold) {
			printCurrentPolynomialPart(roots[rootsCoefficient], rootFolds[rootsCoefficient]);

			rootsCoefficient++;
			currentRootFold = 1;
		}
		else {
			currentRootFold++;
		}

		Px.pop_back();
		PxSize--;
	}
	if (PxSize > 1) {
		std::cout << "(";
		printPolynomial(Px);
		std::cout << ")";
	}
	std::cout << "=0";
	std::cout << std::endl;
}

void printCurrentPolynomialPart(Rational root, int rootFold) {
	bool isPos = isPositive(root);
	std::cout << "(x" << (isPos ? " - " : " + ");
	if (!isPos) {
		root = multiplyRational(root, { -1, 1 });
	}
	printRational(root);
	std::cout << ")";
	if (rootFold >= 2) {
		std::cout << "^" << rootFold;
	}
}