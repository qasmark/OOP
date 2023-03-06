#include "vector_libs.h"

int main()
{
	std::vector<double> nums{};
	if (!ConvertStreamOfNumbersToVector(std::cin, nums))
	{
		std::cout << "An error occured while processing input" << std::endl;
		return 1;
	}

	if (std::size(nums) == 0)
	{
		std::cout << "Nothing to process" << std::endl;
		return 1;
	}

	std::cout << "Vector was:" << std::endl;
	PrintVector(nums);

	AddPositiveAverageValueToAllElement(nums);
	SortVector(nums);

	std::cout << std::endl << "Vector now:" << std::endl;
	PrintVector(nums);
	return 0;
}