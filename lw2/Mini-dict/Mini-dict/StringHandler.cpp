#include "StringHandler.h"

// ���������� �� ������� ������, ������� � ��������� ������ � �����
void TransformStringToLowerCase(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch)); });

}