#include "ConsoleHandler.h"

void Console()
{
	std::string word;

	std::cout << CONSOLE_INPUT << " ";
	std::getline(std::cin, word);

	while (word != "...")
	{
		if (word == "^Z")
		{
			std::cout << "Uncorrect word";
			break;
		}
		std::cout << "You entered the next word: " << word << "\n";

		std::cout << CONSOLE_INPUT << " ";
		std::getline(std::cin, word);
	}
	std::cout << "Changes saved. Goodbye.\n";
}