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

Rational parseCoefficient(const char* str);

bool contains(const char* str, char symbol);

int find(const char* str, char symbol);

char* substring(const char* str, int startIdx, int endIdx);

unsigned int myAtoi(const char* str);

unsigned int myStrlen(const char* str);

bool isEqualToOne(Rational coefficient);

bool isEqualToMinusOne(Rational coefficient);

bool isPositive(Rational coefficient);

Polynomial enterPolynomial();

void printPolynomial(Polynomial polynomial);
//void printPolynomial(std::vector<int>& polynomial, int degree);