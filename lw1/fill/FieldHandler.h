#pragma once

#include <array>
#include <fstream>

constexpr size_t FIELD_SIZE = 100;
constexpr char EMPTY = ' ';
constexpr char BORDER = '#';
constexpr char START = 'O';
constexpr char FILLER = '.';

using Field = std::array<std::array<char, FIELD_SIZE>, FIELD_SIZE>;

Field ReadField(std::istream& inputFile);
void FillField(Field& field);
void PrintField(std::ostream& output, const Field& field);