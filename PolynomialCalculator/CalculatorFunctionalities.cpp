#include "CalculatorFunctionalities.h"
#include "HelperFunctions.h"

void addPolynomials() {
	//std::vector<int> Px = {};
	//std::vector<int> Qx = {};

	//int degreePx = 0, degreeQx = 0;

	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	//printPolynomial(Qx, degreeQx);

	std::cout << "P(x)+Q(x)=";

	std::cout << "----------------------" << std::endl;
}