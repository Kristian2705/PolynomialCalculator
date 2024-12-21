#pragma once

#include <iostream>;
#include <vector>

typedef std::pair<int, int> Rational;
typedef std::vector<Rational> Polynomial;

uint32_t getOption();

bool isValidOption(uint32_t option);

int GCD(int a, int b);

Rational reduce(Rational r);

Rational addRational(Rational a, Rational b);

Rational subtractRational(Rational a, Rational b);

Rational multiplyRational(Rational a, Rational b);

void enterPolynomial(std::vector<int>& polynomial, int& degree);

void printPolynomial(std::vector<int>& polynomial, int degree);