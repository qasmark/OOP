#pragma once

#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	std::size_t pos = 0;
	for (std::size_t i = 0; i < arr.size(); ++i)
	{
		if (less(arr[pos], arr[i]))
		{
			pos = i;
		}
	}
	maxValue = arr[pos];

	return true;
}