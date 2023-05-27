#include "ShapesHandler.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

int main()
{
	//-file
	std::ifstream inputFile;
	inputFile.open("input.txt");
	std::istream& inputStream = inputFile;

	//std::istream& inputStream = std::cin;

	ShapesHandler shapesHandler(inputStream, std::cout);
	while (!inputStream.eof() && !inputStream.fail())
	{
		std::cout << "> ";
		if (!shapesHandler.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	shapesHandler.DrawShaped(800, 600, "Solar System");
	shapesHandler.PrintMaxAreaShape();
	shapesHandler.PrintMinPerimeterShape();
	return 0;
}