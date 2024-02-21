#include "stdafx.h"
#include "RadixFunctions.h"

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

int ConvertArgNotationToInt(const std::string& notation)
{
	int numNotation = 0;

	try
	{
		numNotation = std::stoi(notation);
	}
	catch (...)
	{
		throw std::runtime_error("Error on reading notation argument");
	}

	if (numNotation < 2 || numNotation > 36)
	{
		throw std::runtime_error("Error: notation must be in [2; 36]");
	}

	return numNotation;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument(
			"Invalid arguments count\n"
			"Usage: Radix.exe <source notation> <destination notation> <value>"
		);
	}

	Args args;
	args.sourceNotation = ConvertArgNotationToInt(argv[1]);
	args.destinationNotation = ConvertArgNotationToInt(argv[2]);
	args.value = argv[3];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		std::string result = ConvertToRadix(args->sourceNotation, args->destinationNotation, args->value);
		std::cout << result << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
