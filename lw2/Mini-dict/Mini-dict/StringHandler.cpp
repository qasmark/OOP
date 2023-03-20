#include "StringHandler.h"

// избавиться от лишнего модуля, вынести в локальную функию в дикте
void TransformStringToLowerCase(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch)); });

}