#include "DictHandler.h"

void PrintDictionary(const Dictionary& dictionary, std::ostream& file)
{
	for (const auto& el : dictionary)
	{	
		file << el.first << " " << el.second << "\n";
	}
}

Dictionary GetDictionary(const std::string& fileName, std::ostream& out)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		out << "Cловар€ " << fileName << " нет. Ѕудет создан новый словарь\n";
		return Dictionary();
	}

	Dictionary dictionary;

	while (true)
	{
		std::string engWord, rusWord;

		if (!(file >> engWord) || !(file >> rusWord))
		{
			break;
		}

		TransformStringToLowerCase(engWord);

		dictionary.emplace(engWord, rusWord);
	}

	return dictionary;
}

bool GetTranslation(Dictionary& dictionary, std::istream& in, std::ostream& out)
{
	//change name
	std::string engWord;

	bool isChange = false;

	// вынести услови€ выхода из цикла в условие выхода из цикла
	while (true)
	{
		
		getline(in, engWord);
		

		if (engWord == "...")
		{
			break;
		}

		if (engWord.empty())
		{
			continue;
		}

		TransformStringToLowerCase(engWord);

		auto item = dictionary.find(engWord);
		if (item != dictionary.end())
		{
			//endl
			out << item->second << '\n';
			continue;
		}

		out << "Ќеизвестное слово У" << engWord << "Ф. ¬ведите перевод или пустую строку дл€ отказа.\n";

		std::string translate;
		getline(in, translate);

		if (translate.empty())
		{
			out << "—лово " << engWord << " проигнорировано.\n";
			continue;
		}

		dictionary.emplace(engWord, translate);
		//endl
		out << "—лово У" << engWord << "Ф сохранено в словаре как У" << translate << "Ф.\n";
		isChange = true;
	}

	return isChange;
}

void SaveDictionary(const Dictionary& dictionary, const std::string& fileName, std::ostream& out)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		out << "Cловарь " << fileName << " не может быть сохранен\n";
		return;
	}

	PrintDictionary(dictionary, file);
	out << "»зменени€ сохранены. ƒо свидани€.\n";
}

void WorkWithDictionary(std::istream& in, std::ostream& out)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
	out << "»м€ им€ файла словар€: ";
 	in >> fileName;

	Dictionary dictionary = GetDictionary(fileName, out);

	//change name translationn
	if (GetTranslation(dictionary, in, out))
	{
		//endl
		out << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом.\n";

		//userAnswer
		std::string saver;//change name 

		getline(in, saver);
		if (saver == "Y" || saver == "y")
		{
			SaveDictionary(dictionary, fileName, out);
			return;
		}
		// nit попробовать вынести сохранение в отдельную функцию
	}
}