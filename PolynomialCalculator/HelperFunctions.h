#pragma once

#include <iostream>
#include <vector>

typedef std::pair<int, int> Rational;
typedef std::vector<Rational> Polynomial;

int getOption();

bool isValidOption(int option);

int getDegree();

bool isValidInteger(const char* integer);

bool containsSymbols(const char* str);

void getCoefficient(char* coefficient, int currentDegree);

void getScalar(char* scalar);

bool isValidCoefficient(const char* str);

int GCD(int a, int b);

unsigned int myAbs(int num);

Rational reduce(Rational r);

Rational addRational(Rational a, Rational b);

Rational multiplyRational(Rational a, Rational b);

Rational parseCoefficient(const char* str);

bool contains(const char* str, char symbol);

int find(const char* str, char symbol);

char* substring(const char* str, int startIdx, int endIdx);

unsigned int myAtoi(const char* str);

unsigned int myStrlen(const char* str);

bool isPositive(Rational coefficient);

Polynomial enterPolynomial();

void printPolynomial(Polynomial polynomial);

void printRational(Rational number);

Polynomial add(Polynomial Px, Polynomial Qx);

int getMax(int a, int b);

Polynomial multiplyPolynomialByMinusOne(Polynomial Qx);

Polynomial multiply(Polynomial Px, Polynomial Qx);

void divide(Polynomial Ax, Polynomial Bx);

void trimPolynomial(Polynomial& polynomial);

Polynomial getMultipliedPolynomialByScalar(Polynomial Px, Rational scalar);

Rational getPolynomialValue(Polynomial Px, Rational scalar);

Polynomial getGCD(Polynomial Px, Polynomial Qx);

Polynomial getPolynomialRemainder(Polynomial Px, Polynomial Qx);

void printVietaFormulas(Polynomial Px);

void printFormula(Rational result, int idx, int maxRootNumber, std::vector<std::vector<int>>& subsets);

int getCombinations(int n, int k);

void printSubset(int arr[], int mask, int length, std::vector<int>& subest);

bool compareSubsets(const std::vector<int>& a, const std::vector<int>& b);

void manualSort(std::vector<std::vector<int>>& subsets);

std::vector<std::vector<int>> getSubsets(int arr[], int length);

Polynomial getPowers(Polynomial Px, Rational a);

void printAsPowers(Polynomial result, Rational a, bool isPositiveA);

void displayRootsAndFactors(Polynomial Px);

std::vector<Rational> findFactors(Rational num);

bool containsRoot(std::vector<Rational> possibleRoots, Rational num);

int findLCMOfPolynomialCoefficients(Polynomial Px);

void turnPolynomialCoefficientsIntoIntegers(Polynomial& Px, int lcm, Rational& constantTerm, Rational& leadingCoefficient);

void getPossibleRoots(std::vector<Rational>& possibleRoots, const std::vector<Rational> pFactors, const std::vector<Rational> qFactors);

void getRoots(Polynomial Px, std::vector<Rational>& roots, const std::vector<Rational> possibleRoots);

void getRootFolds(Polynomial Px, std::vector<int>& rootFolds, std::vector<Rational> roots, int rootsCount);

void factorizePolynomial(Polynomial Px, std::vector<Rational> roots, std::vector<int> rootFolds);

void printCurrentPolynomialPart(Rational root, int rootFold);