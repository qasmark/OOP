#include <iostream>
#include "FieldHandler.h"

void InitFiles(std::ifstream& fin, std::ofstream& fout, const std::string& inPath, const std::string& outPath);

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid count of arguments. Using sample: fill.exe <input file> <output file>\n";
		return 1;
	}
	

	try
	{
	    std::ifstream fin;
		std::ofstream fout;
		InitFiles(fin, fout, argv[1], argv[2]);

		Field field = ReadField(fin);
		FillField(field);
		PrintField(fout, field);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}

	return 0;

}

void InitFiles(std::ifstream& fin, std::ofstream& fout, const std::string& inPath, const std::string& outPath)
{
	fin.open(inPath);
	if (!fin.is_open())
	{
		throw std::runtime_error("Failed to open input file.");
	}

	fout.open(outPath);
	if (!fout.is_open())
	{
		throw std::runtime_error("Failed to open output file.");
	}
	return;
}