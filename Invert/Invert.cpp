#include "stdafx.h"

struct Args
{
	std::string inputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			"Invalid arguments count\n"
			"Usage: Invert.exe <matrix file>");
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

float FindDeterminant(float** matrix)
{
	float a = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2];

	float b = matrix[0][2] * matrix[1][1] * matrix[2][0]
		+ matrix[1][2] * matrix[2][1] * matrix[0][0]
		+ matrix[0][1] * matrix[1][0] * matrix[2][2];

	return a - b;
}

float FindMinor(float** matrix, int row, int col)
{
	float minorMatrix[2][2];

	for (int i = 0; i < 3; i++)
	{
		if (i == row)
			continue;

		for (int j = 0; j < 3; j++)
		{
			if (j == col)
				continue;

			// Определяем индексы, по которым будем создавать промежуточную матрицу для подсчёта минора
			int minorRow = i - int(i > row);
			int minorCol = j - int(j > col);

			if (i != row && j != col)
				minorMatrix[minorRow][minorCol] = matrix[i][j];
		}
	}

	return std::powf(-1, row + col) * (minorMatrix[0][0] * minorMatrix[1][1] - minorMatrix[0][1] * minorMatrix[1][0]);
}

void InvertMatrix(float** matrix)
{
	float determinant = FindDeterminant(matrix);
	float transponatedMinorsMatrix[3][3];

	// Находим миноры для исходной матрицы и сразу же транспонируем их
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			transponatedMinorsMatrix[j][i] = FindMinor(matrix, i, j);

	// Записываем результаты инвертирования матрицы заместо исходной матрицы
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix[i][j] = roundf(transponatedMinorsMatrix[i][j] / determinant * 1000) / 1000;
}

void InvertMatrix(const std::string& inputFileName)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Error opening input file!");
	}

	float** matrix = new float*[3];

	for (int i = 0; i < 3; i++)
	{
		matrix[i] = new float[3];
		for (int j = 0; j < 3; j++)
		{
			inputFile >> matrix[i][j];
		}
	}

	if (inputFile.bad())
	{
		throw std::runtime_error("Error reading input file!");
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Input matrix should be 3x3! Make sure there is no empty line at the end");
	}

	InvertMatrix(matrix);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << matrix[i][j];
			if (j != 2)
				std::cout << "\t";
		}

		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		InvertMatrix(args->inputFileName);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}