#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>

void SortVector(std::vector<double>& numbers);
void PrintVector(const std::vector<double>& numbers);
bool ConvertStreamOfNumbersToVector(std::istream& in, std::vector<double>& numbers);
void AddPositiveAverageValueToAllElement(std::vector<double>& numbers);