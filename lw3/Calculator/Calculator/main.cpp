#include "CalculatorController.h"

int main()
{
	Calculator calculator;
	CalculatorController calculatorController(calculator, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!calculatorController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}