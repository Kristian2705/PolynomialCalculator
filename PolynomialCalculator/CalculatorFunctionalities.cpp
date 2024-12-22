#include "CalculatorFunctionalities.h"
#include "HelperFunctions.h"

void addPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);

	std::cout << "P(x)+Q(x)=";

	Polynomial result = add(Px, Qx);
	printPolynomial(result);
	std::cout << "----------------------" << std::endl;
}

void subtractPolynomials() {
	std::cout << "Enter Polynomial P(x)" << std::endl;
	Polynomial Px = enterPolynomial();

	std::cout << "P(x) = ";
	printPolynomial(Px);

	std::cout << "Enter Polynomial Q(x)" << std::endl;
	Polynomial Qx = enterPolynomial();

	std::cout << "Q(x) = ";
	printPolynomial(Qx);
	Qx = multiplyPolynomialByMinusOne(Qx);

	std::cout << "P(x)-Q(x)=";

	Polynomial result = add(Px, Qx);
	printPolynomial(result);

	std::cout << "----------------------" << std::endl;
}