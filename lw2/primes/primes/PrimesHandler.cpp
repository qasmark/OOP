#include "PrimesHandler.h"

std::set<int> GetPrimeNums(int upperBound)
{
	std::vector<bool> primes(upperBound + 1, true);
	std::set<int> result = { 2 };
	int limitOfChecking = static_cast<int>(std::sqrt(primes.size()) + 1);
	for (int i = MIN_BORDER; i <= upperBound; i++)
	{
		std::set<int>::iterator iter = result.lower_bound(limitOfChecking);
		if (primes[i])
		{
			result.insert(iter, i);
			for (int j = i * i; j <= upperBound; j += i)
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