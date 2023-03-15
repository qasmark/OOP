#pragma once

#include "StringHandler.h"
#include <map>
#include <stdexcept>

using WordTranslation = std::vector<std::string>;
using Dict = std::map <std::string, WordTranslation>;

WordTranslation FindTranslation(const Dict& dict, const std::string& word);
void AddForeignTranslation(Dict& dict, const std::string& word, const WordTranslation& translation);
void AddKnownTranslation(Dict& dict, const std::string& word, const WordTranslation& translations);
void AddWordTranslation(Dict& dict, const std::string& word, const WordTranslation& translation);