#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../primes/PrimesHandler.h"

SCENARIO("Tests")
{
	WHEN("Argument out of range")
	{
		REQUIRE_THROWS_AS(GeneratePrimesSet(MIN_BORDER - 1), std::out_of_range);
		REQUIRE_THROWS_AS(GeneratePrimesSet(MAX_BORDER + 1), std::out_of_range);
	}
	WHEN("Lower bordering value")
	{
		auto const primes = GeneratePrimesSet(2);
		std::set<int> answer = { 2 };
		REQUIRE(answer == primes);
	}
	WHEN("Upper bordering value")
	{
		auto const primes = GeneratePrimesSet(100'000'000);
		REQUIRE(primes.size() == 5'761'455);
	}
	WHEN("Same sets with different agruments")
	{
		auto const firstPrimes = GeneratePrimesSet(15);
		auto const secondPrimes = GeneratePrimesSet(16);

		std::set<int> answer = { 2, 3, 5, 7, 11, 13 };
		REQUIRE(firstPrimes == answer);
		REQUIRE(secondPrimes == answer);
	}
	WHEN("sets differ by one prime")
	{
		auto const firstPrimes = GeneratePrimesSet(100);
		auto const secondPrimes = GeneratePrimesSet(102);

		REQUIRE(firstPrimes.size() == 25);
		REQUIRE(secondPrimes.size() == 26);
	}
}