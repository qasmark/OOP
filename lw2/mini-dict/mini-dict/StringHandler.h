#pragma once

#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

std::string ToLowerCaseWithTrim(const std::string& word);
std::vector<std::string> AddStringToVector(const std::string& word, std::vector<std::string> wordList);