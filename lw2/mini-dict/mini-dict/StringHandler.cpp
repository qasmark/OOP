#include "StringHandler.h"

void Trim(std::string& word)
{
	// Erase extra white spaces between parts of word
	word.erase(std::unique(std::begin(word), std::end(word), [](unsigned char a, unsigned char b)
		{ return std::isspace(a) && std::isspace(b); }), std::end(word));


	// Erase white spaces at the end and the start of word
	word.erase(0, word.find_first_not_of(' '));
	word.erase(word.find_last_not_of(' ') + 1);
}

std::string ToLowerCase(const std::string& word)
{
	std::string result;

	for (const char& ch : word)
	{
		result += (std::isalpha(ch)) ? std::tolower(ch) : ch;
	}
	return result;
}

std::string ToLowerCaseWithTrim(const std::string& word)
{
	std::string result;
	result = ToLowerCase(word);
	Trim(result);

	return result;
}

std::vector<std::string> AddStringToVector(const std::string& word, std::vector<std::string> wordList)
{
	for (auto const& value : wordList)
	{
		if (value == word)
		{
			return wordList;
		}
	}
	wordList.push_back(word);

	return wordList;
}