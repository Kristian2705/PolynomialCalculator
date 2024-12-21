#include "CalculatorFunctionalities.h"
#include "HelperFunctions.h"

void addPolynomials() {
	std::vector<int> Px = {};
	std::vector<int> Qx = {};

	int degreePx = 0, degreeQx = 0;

	std::cout << "Enter Polynomial P(x)" << std::endl;
	enterPolynomial(Px, degreePx);

	std::cout << "P(x) = ";
	printPolynomial(Px, degreePx);

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	enterPolynomial(Qx, degreeQx);

	std::cout << "Q(x) = ";
	printPolynomial(Qx, degreeQx);

	std::cout << "P(x)+Q(x)=";

	std::cout << "----------------------" << std::endl;
}