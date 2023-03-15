#include "FileHandler.h"

std::string GetDictPath(int argc, char** argv)
{
	if (argc != 2)
	{
		return DEFAULT_PATH;
	}

	return argv[1];
}

void ReadDictFile(std::istream& dictInFile, Dict& dict)
{
	std::string sourse, translations;

	while (std::getline(dictInFile, sourse))
	{
		if (!std::getline(dictInFile, translations))
		{
			return;
		}

		if (sourse.empty() || translations.empty())
		{
			throw std::invalid_argument("Invalid dictionary file format");
		}
		AddForeignTranslation(dict, sourse, AddStringToVector(translations, {}));
	}
}
