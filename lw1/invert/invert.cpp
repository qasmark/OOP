#include <iostream>
#include <vector>
#include <fstream>
#include <string>

constexpr int MATRIX_SIZE = 3;

using Matrix = std::vector<std::vector<double>>;

Matrix InitMatrix(std::ifstream& file);
double_t Determinant(const Matrix& matrix, bool& mathError);

int main(/*int argc, char* argv*/)
{
	bool wasError = false;
	std::string path;

	std::ifstream file;

	std::cin >> path;

	file.open(path);

	if (!file.is_open())
	{
		std::cout << "File not open.\n";
		return 0;
	}

	Matrix matrix = InitMatrix(file);

	double_t Det = Determinant(matrix, wasError);

	return 0;
}


Matrix InitMatrix(std::ifstream& file)
{
	Matrix matrix;
	std::vector<double> row;
	double_t num;
	std::string str;

	while (getline(file, str))
	{
			
	}

	return matrix;
}

double_t Determinant(const Matrix& matrix, bool& mathError)
{
	// Правило Сюрраса
	double_t det =
		matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][1] * matrix[1][0] * matrix[2][2] -
		matrix[0][0] * matrix[1][2] * matrix[2][1];
	
	return det;
}

