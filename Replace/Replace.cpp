#include "stdafx.h"

// Возвращает результат замены всех вхождения строки searchString внутри строки subject на replacementString
// Если строка searchString пустая, то возвращается subject
std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	const size_t searchLength = searchString.length();
	size_t pos = 0;

	// Результат будет записан в новую строку result, оставляя строку subject неизменной
	std::string result;

	if (searchString.length() > 0)
	{
		while (pos < subject.length())
		{
			// Находим позицию искомой строки, начиная с pos
			size_t foundPos = subject.find(searchString, pos);

			// Если не нашли текст для замены - выходим из цикла и записываем остатки subject
			if (foundPos == std::string::npos)
				break;

			// В результирующую строку записываем текст из диапазона [pos,foundPos)
			result.append(subject, pos, foundPos - pos);

			// В результирующую строку записываем текст для замены
			result.append(replacementString);

			// Пропускаем найденную подстроку
			pos = foundPos + searchLength;
		}
	}

	// Записываем остатки subject в результирующую строку
	result.append(subject, pos, subject.length());

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

void CopyFileWithReplacement(const char* inputFileName, const char* outputFileName,
	const char* searchString, const char* replacementString)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Error opening input file!");
	}

	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Error opening output file!");
	}

	std::string search = searchString;
	std::string replace = replacementString;

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);

	if (inputFile.bad())
	{
		throw std::runtime_error("Error reading input file!");
	}

	if (!outputFile.flush())
	{
		throw std::runtime_error("Error writing to output file!");
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	try
	{
		CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
