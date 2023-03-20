#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Mini-dict/DictHandler.h"
#include "../Mini-dict/StringHandler.h"

#include <sstream>

SCENARIO("Check getting dictionary")
{
	WHEN("Check getting dictionary from null file")
	{
		std::string fileName("emptyTest.txt");
		std::stringstream out;

		Dictionary dictionary;

		REQUIRE(GetDictionary(fileName, out) == dictionary);
		REQUIRE(out.str().empty());
	}

	WHEN("Check getting dictionary from defunct file")
	{
		std::string fileName("notExistFile.txt");
		std::stringstream out;

		Dictionary dictionary;

		REQUIRE(GetDictionary(fileName, out) == dictionary);
		REQUIRE(out.str() == "Cловаря notExistFile.txt нет. Будет создан новый словарь\n");
	}
}

SCENARIO("Check saving dictionary")
{
	WHEN("Check saving dictionary")
	{
		std::string file = "cat";
		std::stringstream out;

		Dictionary dictionary = { { "cat", "кошка" }, { "dog", "собака" } };

		SaveDictionary(dictionary, file, out);
		REQUIRE(out.str() == "Изменения сохранены. До свидания.\n");
	}
}

SCENARIO("Check transform string to lower case")
{
	WHEN("Check transform string to lower case")
	{
		std::string string = "cAT";
		TransformStringToLowerCase(string);
		REQUIRE(string == "cat");

		string = "CaT";
		TransformStringToLowerCase(string);
		REQUIRE(string == "cat");

		string = "CAT";
		TransformStringToLowerCase(string);
		REQUIRE(string == "cat");
	}
}

SCENARIO("Check tranlate word")
{
	WHEN("Check tranlate existing word")
	{
		std::stringstream in("cat\n...\n");
		std::stringstream out;

		Dictionary dictionary = { { "cat", "кошка" }, { "dog", "собака" } };

		REQUIRE(!GetTranslation(dictionary, in, out));
		REQUIRE(out.str() == "кошка\n");
	}

	WHEN("Check tranlate defunct word")
	{
		std::stringstream in("cats\nкоты\ncats\n...\n");
		
		std::stringstream out;

		Dictionary dictionary;

		REQUIRE(GetTranslation(dictionary, in, out));

		Dictionary res = { { "cats", "коты" } };

		REQUIRE(res == dictionary);

		in.str("cat\n\n...\n");
		out.str("");

		REQUIRE(!GetTranslation(dictionary, in, out));
		REQUIRE(res == dictionary);
	}

	WHEN("Check tranlate existing in different case word")
	{
		std::stringstream in("caT\nCAT\nCaT\nDOg\n...\n");
		std::stringstream out;

		Dictionary dictionary = { { "cat", "кошка" }, { "dog", "собака" } };

		REQUIRE(!GetTranslation(dictionary, in, out));
		REQUIRE(out.str() == "кошка\nкошка\nкошка\nсобака\n");
	}
}