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

#include "CalculatorFunctionalities.h"
#include "HelperFunctions.h"
#include "Constants.h"

void addPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);
	std::cout << std::endl << std::endl;

	std::cout << "P(x)+Q(x)=";

	Polynomial result = add(Px, Qx);
	printPolynomial(result);
	std::cout << std::endl << std::endl;
	std::cout << "----------------------" << std::endl;
}

void subtractPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);
	std::cout << std::endl << std::endl;
	Qx = multiplyPolynomialByMinusOne(Qx);

	std::cout << "P(x)-Q(x)=";

	Polynomial result = add(Px, Qx);
	printPolynomial(result);
	std::cout << std::endl << std::endl;

	std::cout << "----------------------" << std::endl;
}

void multiplyPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);
	std::cout << std::endl << std::endl;

	std::cout << "P(x)*Q(x)=";

	Polynomial result = multiply(Px, Qx);
	printPolynomial(result);
	std::cout << std::endl << std::endl;

	std::cout << "----------------------" << std::endl;
}

void dividePolynomials() {
	std::cout << "Enter Polynomial A(x)" << std::endl;
	Polynomial Ax = enterPolynomial();

	std::cout << "A(x) = ";
	printPolynomial(Ax);
	std::cout << std::endl << std::endl;

	std::cout << "Enter Polynomial B(x)" << std::endl;
	Polynomial Bx = enterPolynomial();

	std::cout << "B(x) = ";
	printPolynomial(Bx);
	std::cout << std::endl << std::endl;

	divide(Ax, Bx);

	std::cout << "----------------------" << std::endl;
}

void multiplyPolynomialByScalar() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	char scalar[MAX_BUFFER_SIZE];
	getScalar(scalar);
	Rational scalarRational = parseCoefficient(scalar);

	std::cout << "Result:";

	Polynomial result = getMultipliedPolynomialByScalar(Px, scalarRational);
	printPolynomial(result);
	std::cout << std::endl << std::endl;
	std::cout << "----------------------" << std::endl;
}

void findPolynomialValue() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	char scalar[MAX_BUFFER_SIZE];
	getScalar(scalar);
	Rational scalarRational = parseCoefficient(scalar);

	Rational result = getPolynomialValue(Px, scalarRational);

	std::cout << "P(";
	printRational(scalarRational);
	std::cout << ") = ";
	printRational(result);
	std::cout << std::endl;

	std::cout << "----------------------" << std::endl;
}

void findGCDofPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);
	std::cout << std::endl << std::endl;

	std::cout << "gcd(P(x), Q(x)) = ";

	Polynomial result = getGCD(Px, Qx);
	printPolynomial(result);
	std::cout << std::endl << std::endl;
	std::cout << "----------------------" << std::endl;
}

void displayVietaFormulas() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << std::endl;
	std::cout << "Vieta's formulas for polynomial: P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	printVietaFormulas(Px);

	std::cout << "----------------------" << std::endl;
}

void expressAsPowers() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	char a[MAX_BUFFER_SIZE];
	getScalar(a);
	Rational aRational = parseCoefficient(a);

	if (aRational.first == 0) {
		std::cout << "P(x) = ";
		printPolynomial(Px);
		std::cout << std::endl << std::endl;
	}
	else {
		std::cout << "P(x";

		bool isPositiveA = isPositive(aRational);
		if (isPositiveA) {
			std::cout << "+";
		}

		printRational(aRational);

		std::cout << ") = ";

		Polynomial result = getPowers(Px, aRational);
		printAsPowers(result, aRational, isPositiveA);

	}
	std::cout << "----------------------" << std::endl;
}

void findRootsAndFactors() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);
	std::cout << std::endl << std::endl;

	displayRootsAndFactors(Px);

	std::cout << "----------------------" << std::endl;
}