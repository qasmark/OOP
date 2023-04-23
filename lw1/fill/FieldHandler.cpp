#include "FieldHandler.h"


Field ReadField(std::istream& inputFile)
{
	char ch;
	size_t row = 0;
	size_t column = 0;
	Field field;
	bool isStartFound = false;

	std::fill(&field[0][0], &field[FIELD_SIZE - 1][FIELD_SIZE - 1], EMPTY);

	if (inputFile.bad())
	{
		throw std::runtime_error("Failed to read from input file");
	}

	while (!inputFile.eof())//  переписать
	{
		inputFile.get(ch);

		if (ch == START)
		{
			isStartFound = true;
		}

		switch (ch)
		{
		case START:
		case EMPTY:
		case BORDER:
			field[row][column++] = ch;
				break;
		case '\n':
			row++;
			column = 0;
			break;
		default:
			throw std::invalid_argument("Indefined character");
		}

		if (column == FIELD_SIZE - 1)
		{
			column = 0;
			inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (row == FIELD_SIZE - 1)
		{
			break;
		}
	}

	if (!isStartFound)
	{
		throw std::invalid_argument("Start point doesn't found.");
	}

	return field;
}

void FillCell(Field& field, size_t row, size_t column)
{
	char& cell = field[row][column];
	if (cell == EMPTY || cell == START)
	{
		if (cell == EMPTY)
		{
			cell = FILLER;
		}

		if (column > 0)
		{
			FillCell(field, row, column - 1);
		}

		if (row > 0)
		{
			FillCell(field, row - 1, column);
		}

		if (column < FIELD_SIZE - 1)
		{
			FillCell(field, row, column + 1);
		}

		if (row < FIELD_SIZE - 1)
		{
			FillCell(field, row + 1, column);
		}
	}
}
// рекурсивный подход приведет к переполнению стека вызовов
void FillField(Field& field)
{
	for (size_t row = 0; row < FIELD_SIZE; ++row)
	{
		for (size_t column = 0; column < FIELD_SIZE; ++column)
		{
			if (field[row][column] == START)
			{
				FillCell(field, row, column);
			}
		}
	}
}

void PrintField(std::ostream& output, const Field& field)
{
	for (size_t row = 0; row < FIELD_SIZE; ++row)
	{
		for (size_t column = 0; column < FIELD_SIZE; ++column)
		{
			output << field[row][column];
		}
		output << '\n';
	}

	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output file");
	}
}
// тесты не расширяемы 