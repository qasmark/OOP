#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../FindMaxEx/FindMax.hpp"
#include "../FindMaxEx/Sportsmen.h"

TEST_CASE("Function can find max element in not empty array")
{
	WHEN("Array is not empty and try to find max by height")
	{
		const std::vector<Sportsmen> arr = {
			{"Oleg Olegov Olegovich", 156, 54},
			{"Andrei Andreev Andreevich", 170, 67},
			{"Suvorov Ivan Ivanovich", 190, 54},
			{"Chichikov Alex Alexeev", 195, 89}
		};
		Sportsmen maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessHeight);

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.height == 195);
		}
	}

	WHEN("Array is not empty and try to find max from numbers")
	{
		const std::vector<int> arr = {
			0, 1, 2, 3, 4, -1
		};
		int maxValue;
		const bool result = FindMax(arr, maxValue, [](const int left, const int right) {return left < right; });

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue == 4);
		}
	}

	WHEN("Array is not empty and try to find max by weight")
	{
		const std::vector<Sportsmen> arr = {
			{"Ivan Ivanov Ivanovich", 156, 60},
			{"Oleg Olegov Olegovich", 192, 85},
			{"Alexander Alexandrov Alexandrovich", 193, 91},
			{"Nikolay Nikolaev Nikolaevich", 160, 91},
			{"Chuvak Chuvakov Chikov", 175, 72}
		};
		Sportsmen maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.weight == 91);
		}
	}

	WHEN("Array has one element and try to find max by weight")
	{
		const std::vector<Sportsmen> arr = {
			{"Oleg Olegov Olegovich", 180, 88}
		};
		Sportsmen maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function should return this element")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.weight == 88);
		}
	}

	WHEN("Array has one element and try to find max by height")
	{
		const std::vector<Sportsmen> arr = {
			{"Oleg Olegov Olegovich", 180, 88}
		};
		Sportsmen maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessHeight);

		THEN("Function should return this element")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.height == 180);
		}
	}

	WHEN("Array has one element and try to find max from numbers")
	{
		const std::vector<int> arr = {
			-1
		};
		int maxValue;
		const bool result = FindMax(arr, maxValue, [](const int left, const int right) {return left < right; });

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue == -1);
		}
	}

	WHEN("Array has two element and try to find max from numbers")
	{
		const std::vector<int> nums = {
			-1, 1
		};
		int maxValue;
		const bool result = FindMax(nums, maxValue, [](const int left, const int right) {return left < right; });

		THEN("Function can find max in nums")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue == 1);
		}
	}

	WHEN("Function can't find max element in empty array")
	{
		const std::vector<Sportsmen> arr = {};
		Sportsmen maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function should return false")
		{
			REQUIRE(result == false);
		}
	}
}