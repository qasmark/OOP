#pragma once

#include <set>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

constexpr int MIN_BORDER = 2;
constexpr int MAX_BORDER = 100'000'000;

std::set<int> GeneratePrimesSet(int upperBound);
void PrintPrimes(std::ostream& out, const std::set<int>& primes);