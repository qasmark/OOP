#include "PrimesHandler.h"

std::set<int> GetPrimes(int upperBound)
{
	// add assert when upperBound less then 2 
	// добавить комментарий для ограниченного диапазона использования

	std::vector<bool> primes(upperBound + 1, true);
	std::set<int> result;

	result.insert(2);
	const double sizeSquareRoot = std::sqrt(primes.size());

	for (size_t i = 3; i < primes.size(); i += 2) // ускорить внешний цикл 
	{
		if (!primes[i])
		{
			continue;
		}

		result.insert(static_cast<int>(i));

		if (i < sizeSquareRoot)
		{
			for (size_t j = i * i; j < primes.size(); j += i) // ускорить вн. цикл 
			{
				primes[j] = false;
			}
		}
	}

	return result;
}

std::set<int> GeneratePrimesSet(int upperBound)
{
	if (upperBound < MIN_BORDER || upperBound > MAX_BORDER)
	{
		throw std::out_of_range("Invalid upper bound value");
	}

	return GetPrimes(upperBound);
}

void PrintPrimes(std::ostream& out, const std::set<int>& primes)
{
	std::copy(
		primes.begin(),
		primes.end(),
		std::ostream_iterator<int>(out, "\n"));
	out << '\n';
}