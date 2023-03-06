#define CATCH_CONFIG_MAIN
#include "..\catch2\catch.hpp"
#include "..\vector\vector_libs.h"

bool ApproximatelyEquals(const std::vector<double>& one, const std::vector<double>& two)
{
	return std::equal(
		one.begin(),
		one.end(),
		two.begin(),
		[](double a, double b) -> bool {
			return std::abs(a - b) < std::numeric_limits<double>::epsilon();
		});
}

TEST_CASE("vector is read correctly")
{
	std::stringstream input;

	SECTION("reading empty input results in an empty vector")
	{
		input.str("");
		std::vector<double> nums;
		auto status = ConvertStreamOfNumbersToVector(input, nums);

		REQUIRE(nums.empty());
	}

	SECTION("numbers are read correctly")
	{
		input.str("1 2 3 q");
		std::vector<double> nums;
		auto status = ConvertStreamOfNumbersToVector(input, nums);
		std::vector<double> result = { 1, 2, 3 };

		REQUIRE(nums == result);
	}

	SECTION("no numbers input results in an exception")
	{
		input.str("not a number");
		std::vector<double> nums;
		REQUIRE_THROWS_AS(ConvertStreamOfNumbersToVector(input, nums), std::invalid_argument);
	}

	SECTION("input containing several lines is read correctly")
	{
		input.str("1\n2\n3\nq");
		std::vector<double> nums;

		auto status = ConvertStreamOfNumbersToVector(input, nums);
		std::vector<double> result = { 1, 2, 3 };

		REQUIRE(nums == result);
	}
}

TEST_CASE("vector is processed correctly")
{
	SECTION("empty vector results in an empty vector")
	{
		std::vector<double> vector;
		AddPositiveAverageValueToAllElement(vector);

		REQUIRE(vector.empty());
	}

	SECTION("vector of all positive elements is processed correctly")
	{
		std::vector<double> nums = { 1, 2, 3 };
		AddPositiveAverageValueToAllElement(nums);
		std::vector<double> result = { 3, 4, 5 };

		REQUIRE(ApproximatelyEquals(nums, result));
	}

	SECTION("vector of all negative elements is not changed")
	{
		std::vector<double> nums{ -1, -2, -3 };
		AddPositiveAverageValueToAllElement(nums);
		std::vector<double> result{ -1, -2, -3 };

		REQUIRE(nums == result);
	}

	SECTION("mixed positive-negative and zeros vector is processed correctly")
	{
		std::vector<double> nums = { 1, 0, 0, -1, 2, 3, -5 };
		AddPositiveAverageValueToAllElement(nums);
		std::vector<double> result = { 3, 2, 2, 1, 4, 5, -3 };

		REQUIRE(ApproximatelyEquals(nums, result));
	}

	SECTION("all zeros vector results is not changed")
	{
		std::vector<double> nums(42, 0);
		AddPositiveAverageValueToAllElement(nums);
		std::vector<double> result(42, 0);

		REQUIRE(nums == result);
	}
}

TEST_CASE("vector is printed correctly")
{
	std::stringstream ss;
	SECTION("usual vector results in a fixed-number output")
	{
		std::vector<double> nums{ 1, 2.5431, 2.5, 3.5439 };
		PrintVector(nums);
		REQUIRE(ss.str() == "1.000 2.543 2.500 3.544 \n");
	}
}