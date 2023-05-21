#include "Sportsmen.h"

bool CompareLessHeight(const Sportsmen& left, const Sportsmen& right) {
	return left.height < right.height;
}

bool CompareLessWeight(const Sportsmen& left, const Sportsmen& right)
{
	return left.weight < right.weight;
}