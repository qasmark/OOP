#pragma once
#include <string>

struct Sportsmen
{
	std::string name;
	size_t height;
	size_t weight;
};

bool CompareLessHeight(const Sportsmen& left, const Sportsmen& right);
bool CompareLessWeight(const Sportsmen& left, const Sportsmen& right);