#include "stdafx.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string search;
	std::string replace;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.search = argv[3];
	args.replace = argv[4];
	return args;
}

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
			size_t foundPos = subject.find(searchString, pos);

			if (foundPos == std::string::npos)
				break;

			result.append(subject, pos, foundPos - pos);
			result.append(replacementString);

			// Пропускаем найденную подстроку
			pos = foundPos + searchLength;
		}
	}

	// Записываем остатки subject в результирующую строку
	result.append(subject, pos, subject.length());

	return result;
}

void CopyWithReplacement(std::istream& input, std::ostream& output,
	const std::string& search, const std::string& replace)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, search, replace) << "\n";
	}
}

void CopyWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& search, const std::string& replace)
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

	CopyWithReplacement(inputFile, outputFile, search, replace);

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
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	try
	{
		CopyWithReplacement(args->inputFileName, args->outputFileName, args->search, args->replace);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
