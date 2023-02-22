#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int StringToInt(const std::string& str, int radix, bool& wasError);
int CharToInt(char ch, int radix);
std::string IntToString(int num, int radix, bool& wasError);
char IntToChar(int num);
bool IsIntegerOverflow(int num, int radix, int digit); // digit <-> radix
bool IsValidRadix(const std::string& radix);

int main(int argc, char** argv)
{
	bool wasError = false;
	std::string sourNotation, destNotation, value;

	if (argc != 4)
	{
		std::cout << "Invalid count of arguments. using next example: radix.exe <source notation> <destination notation> <value>\n";
		return 0;
	}

	sourNotation = argv[1];
	destNotation = argv[2];
	value = argv[3];

	if (!IsValidRadix(sourNotation))
	{
		std::cout << "Validation error\n";
		return 1;
	}
	if (!IsValidRadix(destNotation))
	{
		std::cout << "Validation error\n";
		return 1;
	}

	int num = StringToInt(value, stoi(sourNotation), wasError);

	if (wasError)
	{
		std::cout << "Integer error\n";
		return 1;
	}

	std::cout << IntToString(num, stoi(destNotation), wasError) << std::endl;

	return 0;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	bool isLessZero = str[0] == '-';
	int num = 0;

	if (str.length() == 0)
	{
		wasError = true;
		return 0;
	}
	 
	for (size_t i = isLessZero ? 1 : 0; i < str.length(); ++i)
	{
		int temp = CharToInt(str[i], radix);

		if (temp == -1)
		{
			wasError = true;
			return 0;
		}
		if (IsIntegerOverflow(num, radix, temp))
		{
			wasError = true;
			return 0;
		}
		

		num = num * radix + temp;
	}

	return (isLessZero) ? -num : num;
}

std::string IntToString(int num, int radix, bool& wasError)
{
	std::string numInStr;

	bool isLessZero = num < 0;
	if (isLessZero)
		num *= -1;

	do
	{
		int digit = num % radix;
		numInStr.push_back(IntToChar(digit));

		num /= radix;
	} while (num != 0);

	if (isLessZero)
		numInStr.push_back('-');
	
	std::reverse(numInStr.begin(), numInStr.end());

	return numInStr;
}

int CharToInt(char ch, int radix)					
{																					// ASCII_letter 
	if (ch >= '0' && ch <= '9' && (ch - '0') < radix)								// 48 code - 0, 57 code - 9 
		return ch - '0';															// example: '5' = 53, '5' - '0' = 5 (int)
	else if (ch >= 'A' && ch <= 'Z' && (ch - 'A' + 10) < radix)					// 65 code - A,  90 code - Z
		return ch - 'A' + 10;														// example: F = 70, 70 - 65 + 10 = 15 (int)
	else
		return -1;
}

char IntToChar(int num)
{
	if (num >= 0 && num <= 9)
		return num + '0';
	else
		return num + 'A' - 10;
}

bool IsIntegerOverflow(int num, int radix, int digit)
{
	if (num > (INT_MAX - digit) / radix)
		return true;
	else
		return false;
}

bool IsValidRadix(const std::string& radix)
{
	if (radix.length() == 0)
	{
		return false;
	}
	for (size_t i = 0; i < radix.length(); ++i)
	{
		if (radix[i] > '9' || radix[i] < '0')
		{
			return false;
		}
	}
	if (stoi(radix) < 2 || stoi(radix) > 36)
	{
		return false;
	}
	
	return true;
}