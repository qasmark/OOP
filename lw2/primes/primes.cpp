#include "PrimesHandler.h"
#include <ctime>

int main(int argc, char** argv)
{ 
	clock_t time = clock();

	if (argc != 2)
	{
		std::cout << "Invalid count of argument. Use the sample: primes.exe <number>\n";
		return 1;
	}
	int upperBound;
	try
	{
		upperBound = std::stoi(argv[1]);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}
	try
	{
		auto const primes = GeneratePrimeNumbersSet(upperBound);
//		PrintPrimes(std::cout, primes);
		std::cout << "The count of primes is " << GetLenghtOfSet(primes) << "\n";
		std::cout << "The time execution is " << (double)(clock() - time) / 1000 << " s.\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}