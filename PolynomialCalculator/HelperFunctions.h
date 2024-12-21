#pragma once

#include <iostream>;
#include <vector>

uint32_t getOption();

bool isValidOption(uint32_t option);

void enterPolynomial(std::vector<int>& polynomial, int& degree);

void printPolynomial(std::vector<int>& polynomial, int degree);