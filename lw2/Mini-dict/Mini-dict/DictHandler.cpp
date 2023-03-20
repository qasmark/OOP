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
		out << "C������ " << fileName << " ���. ����� ������ ����� �������\n";
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

	// ������� ������� ������ �� ����� � ������� ������ �� �����
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

		out << "����������� ����� �" << engWord << "�. ������� ������� ��� ������ ������ ��� ������.\n";

		std::string translate;
		getline(in, translate);

		if (translate.empty())
		{
			out << "����� " << engWord << " ���������������.\n";
			continue;
		}

		dictionary.emplace(engWord, translate);
		//endl
		out << "����� �" << engWord << "� ��������� � ������� ��� �" << translate << "�.\n";
		isChange = true;
	}

	return isChange;
}

void SaveDictionary(const Dictionary& dictionary, const std::string& fileName, std::ostream& out)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		out << "C������ " << fileName << " �� ����� ���� ��������\n";
		return;
	}

	PrintDictionary(dictionary, file);
	out << "��������� ���������. �� ��������.\n";
}

void WorkWithDictionary(std::istream& in, std::ostream& out)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
	out << "��� ��� ����� �������: ";
 	in >> fileName;

	Dictionary dictionary = GetDictionary(fileName, out);

	//change name translationn
	if (GetTranslation(dictionary, in, out))
	{
		//endl
		out << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";

		//userAnswer
		std::string saver;//change name 

		getline(in, saver);
		if (saver == "Y" || saver == "y")
		{
			SaveDictionary(dictionary, fileName, out);
			return;
		}
		// nit ����������� ������� ���������� � ��������� �������
	}
}