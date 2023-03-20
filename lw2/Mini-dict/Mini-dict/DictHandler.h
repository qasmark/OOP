#pragma once

#include "StringHandler.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <Windows.h>

using Dictionary = std::map < std::string, std::string >;

void WorkWithDictionary(std::istream& in, std::ostream& out);
// ������� � ��������� ����� ��� ������������
// LoadDictionaryFromFile
// ��������� ������� � ����������� ������ WorkWithDictionary, ��� ������ ����
Dictionary GetDictionary(const std::string& fileName, std::ostream& out);
bool GetTranslation(Dictionary& dictionary, std::istream& in, std::ostream& out);
void SaveDictionary(const Dictionary& dictionary, const std::string& fileName, std::ostream& out);