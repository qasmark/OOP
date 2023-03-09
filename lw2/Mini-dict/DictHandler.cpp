#include "DictHandler.h"

WordTranslation FindTranslation(const Dict& dict, const std::string& word)
{
	try
	{
		return dict.at(ToLowerCaseWithTrim(word));
	} 
	catch (const std::out_of_range&)
	{
		return { "No variants of translate. " };
	}
}

void AddNewTranslation(Dict& dict, const std::string& word, const WordTranslation& translation)
{
	const std::string wordInLower = ToLowerCaseWithTrim(word);
	
	auto iter = dict.find(wordInLower);
	if (iter == dict.end())
	{
		dict[wordInLower] = translation;
	}
	else
	{
		for (auto const& typeTranslation : translation)
		{
			iter->second.push_back(typeTranslation);
		}
	}
}

void AddReverseTranslation(Dict& dict, const std::string& word, const WordTranslation& translations)
{
	for (auto const& transaltion : translations)
	{
		auto const translationInLower = ToLowerCaseWithTrim(transaltion);
		auto iter = dict.find(translationInLower);
		if (iter == dict.end())
		{
			dict[translationInLower] = { word };
		}
		else
		{
			iter->second.push_back(word);
		}
	}
}
