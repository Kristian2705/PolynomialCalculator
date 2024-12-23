#pragma once

#include <iostream>
#include <vector>

typedef std::pair<int, int> Rational;
typedef std::vector<Rational> Polynomial;

uint32_t getOption();

bool isValidOption(uint32_t option);

int getDegree();

bool isValidDegree(int degree);

void getCoefficient(char* coefficient, int currentDegree);

bool isValidCoefficient(const char* str);

int GCD(int a, int b);

unsigned int myAbs(int num);

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

Polynomial add(Polynomial Px, Polynomial Qx);

Polynomial multiplyPolynomialByMinusOne(Polynomial Qx);

int getMax(int a, int b);

int getMin(int a, int b);