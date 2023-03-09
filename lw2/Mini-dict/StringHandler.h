#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

std::string ToLowerCaseWithTrim(const std::string& word);
std::vector<std::string> AddStringToVector(const std::string& word, std::vector<std::string> wordList);