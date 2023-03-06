#include "vector_libs.h"

bool ConvertStringToDouble(const std::string& input, double& value)
{
	std::stringstream stream{};

	stream << input;
	stream >> value;

	if (stream.fail())
	{
		return true;
	}
	return false;
}

bool ConvertStreamOfNumbersToVector(std::istream& in, std::vector<double>& numbers)
{
	bool isValidValue = true;
	double value;
	std::istream_iterator<std::string> iter{ in }, end;

	if (iter == end)
	{
		return true;
	}
	for (; iter != end; iter++)
	{
		isValidValue = ConvertStringToDouble((*iter), value);

		if (*iter == "Q" || *iter == "q" || isValidValue)
		{
			return isValidValue;
;		}
		numbers.push_back(value);
	}
	numbers.shrink_to_fit();
}

constexpr auto PRINT_WIDTH = 5;
constexpr auto PRINT_PRECISION = 4; 
double FindPositiveAverageValue(const std::vector<double>& numbers)
{
	double sum = 0;
	double countPositiveNumbers = 0;

	for (const double& num : numbers)
	{
		if (num > 0)
		{
			countPositiveNumbers++;
			sum += num;
		}
	}
	
	if (countPositiveNumbers == 0)
	{
		return 0;
	}

	return sum / countPositiveNumbers;
}

void AddPositiveAverageValueToAllElement(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}
	auto positiveAverageValue = FindPositiveAverageValue(numbers);

	if (positiveAverageValue == 0)
	{
		return;
	}

	for (double& num : numbers)
	{
		num += positiveAverageValue;
	}
}

void SortVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}

void PrintVector(const std::vector<double>& numbers)
{
	if (numbers.size() == 0)
	{
		return;
	}
	for (const auto& val : numbers)
	{
		std::cout << "|";
		std::cout.width(PRINT_WIDTH);
		std::cout.precision(PRINT_PRECISION);
		std::cout.right;
		std::cout << val + 0.0;
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}