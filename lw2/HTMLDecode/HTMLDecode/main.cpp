#include "HTMLManager.h"
#include <fstream>
int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	HtmlDecodeInStreams(fin, fout);
	HtmlDecodeInStreams(std::cin, std::cout);

	return 0;
}