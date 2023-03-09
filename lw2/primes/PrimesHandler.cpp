#include "PrimesHandler.h"

using row = std::vector<bool>;

std::set<int> GetPrimeNums(int upperBound)
{
	row primes(upperBound, true);
	std::set<int> result = {2};

	const double sizeSquareRoot = std::sqrt(primes.size());

	for (size_t i = 3; i < primes.size(); i += 2)
	{
		if (primes[i])
		{
			result.insert(static_cast<int>(i));

			if (i < sizeSquareRoot)
			{
				for (size_t j = i * i; j < primes.size(); j += i)
				{
					primes[j] = false;
				}
			}
		}
	}

	return result;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_BORDER || upperBound > MAX_BORDER)
	{
		throw std::out_of_range("Invalid upper bound value");
	}

	return GetPrimeNums(upperBound);
}

void PrintPrimes(std::ostream& out, const std::set<int>& primes)
{
	std::copy(
		primes.begin(),
		primes.end(),
		std::ostream_iterator<int>(out, "\n"));
	out << '\n';
}

int GetLenghtOfSet(std::set<int> primes)
{
	return primes.size();
}