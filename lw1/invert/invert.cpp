#include <iostream>
#include <array>
#include <fstream>
#include <iomanip>

constexpr int MATRIX_SIZE = 3;
constexpr int SIZE_OF_SEPARATOR = 4;

using Matrix = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

bool IsValidInputParameters(int count, char** values, std::ifstream& fin);
Matrix InitializeMatrix(std::istream& fin, bool& wasError);
double GetDeterminantMatrix(const Matrix& matrix);
Matrix GetAdjencyMatrix(const Matrix& matrix, double det);
void PrintMatrix(const Matrix& matrix);
Matrix TransposeMatrix(const Matrix& matrix);

int main(int argc, char** argv)
{
	bool wasError;
	std::ifstream fin;

	if (!IsValidInputParameters(argc, argv, fin))
	{
		return 1;
	}

	fin.open(argv[1]);
	if (!fin.is_open())
	{
		std::cout << "File not exist\n";
		return 1;
	}

	auto matrix = InitializeMatrix(fin, wasError);
	if (wasError)
	{
		return 1;
	}

	double detMatrix = GetDeterminantMatrix(matrix); // union det and adjency

	if (detMatrix == 0)
	{
		std::cout << "The inverse matrix doesn't exist\n";
		return 1;
	}
	Matrix inverseMatrix = GetAdjencyMatrix(matrix, detMatrix);
	inverseMatrix = TransposeMatrix(inverseMatrix);

	std::cout << "Inverse matrix is: \n";
	PrintMatrix(inverseMatrix);

	return 0;
}

bool IsValidInputParameters(int count, char** values, std::ifstream& fin)
{
	if (count != 2)
	{
		std::cout << "Invalid count of arguments. Using sample: invert.exe <matrix file1>\n";
		return false;
	}
	return true;
}

Matrix InitializeMatrix(std::istream& fin, bool& wasError)
{
	Matrix matrix = {};
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			if (!(fin >> matrix[row][column]))
			{
				std::cout << "Invalid matrix format\n";

				wasError = true;
				matrix = { {0} };
				return matrix;
			}
		}
	}
	return matrix;
}

double GetDeterminantMatrix(const Matrix& matrix)
{
	// Правило Сюрраса для матрицы третьего порядка
	return matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][1] * matrix[1][0] * matrix[2][2] -
		matrix[0][0] * matrix[1][2] * matrix[2][1];
}

Matrix GetAdjencyMatrix(const Matrix& matrix, double det)
{
	// Метод алг. дополнений для поиска сопряженной матрицы
	Matrix result = {};
	result[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	result[0][1] = -1 * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	result[0][2] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
	result[1][0] = -1 * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]);
	result[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	result[1][2] = -1 * (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
	result[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
	result[2][1] = -1 * (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
	result[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

	// Деление на определитель
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			result[row][column] = (double) result[row][column] / det;
		}
	}
	return result;
}

void PrintMatrix(const Matrix& matrix)
{
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; column++)
		{
			std::cout << matrix[row][column] << std::setprecision(SIZE_OF_SEPARATOR);
		}
		std::cout << "\n";
	}
}

Matrix TransposeMatrix(const Matrix& matrix)
{
	Matrix result = {};
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			if (matrix[column][row] == -0)
			{
				result[row][column] = 0;
			}
			else
			{
				result[row][column] = matrix[column][row];
			}
		}
	}
	return result;
}