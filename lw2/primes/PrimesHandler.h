#pragma once

#include <set>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

constexpr int MIN_BORDER = 2;
constexpr int MAX_BORDER = 100'000'0000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimes(std::ostream& out, const std::set<int>& primes);
int GetLenghtOfSet(std::set<int> primes);