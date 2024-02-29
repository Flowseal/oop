#include "stdafx.h"

struct Args
{
	std::string operation;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

char ShuffleByte(char ch)
{
	ch = (ch & 0xF0) >> 4 | (ch & 0x0F) << 4;
	ch = (ch & 0xCC) >> 2 | (ch & 0x33) << 2;
	ch = (ch & 0xAA) >> 1 | (ch & 0x55) << 1;
	return ch;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Invalid argument count\n"
									"Usage: crypt.exe <crypt/decrypt> <input file> <output file> <key>\n");
	}
	Args args;
	args.operation = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	try
	{
		args.key = std::stoi(argv[4]);
		if (args.key < 0 || args.key > 255)
			throw std::exception();
	}
	catch (...)
	{
		throw std::invalid_argument("Error on reading key arguemnt: key must be in [0; 255]");
	}

	if (args.operation != "crypt" && args.operation != "decrypt")
	{
		throw std::invalid_argument("Invalid operation!\n"
									"Usage: crypt.exe <crypt/decrypt> <input file> <output file> <key>\n");
	}

	return args;
}

void Decrypt(std::istream& input, std::ostream& output, int key)
{
	char ch;
	while (input.get(ch))
	{
		output.put(char(ShuffleByte(ch) ^ key));
	}
}

void Crypt(std::istream& input, std::ostream& output, int key)
{
	char ch;
	while (input.get(ch))
	{
		output.put(ShuffleByte(ch ^ key));
	}
}

void FileCipher(const std::string& operation, const std::string& inputFileName,
	const std::string& outputFileName, int key)
{
	// TODO вынести проверку файлов
	std::ifstream inputFile(inputFileName, std::ios_base::binary);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Error opening input file!");
	}

	std::ofstream outputFile(outputFileName, std::ios_base::binary);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Error opening output file!");
	}

	if (operation == "crypt")
		Crypt(inputFile, outputFile, key);
	else
		Decrypt(inputFile, outputFile, key);

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
	try
	{
		auto args = ParseArgs(argc, argv);
		FileCipher(args->operation, args->inputFileName, args->outputFileName, args->key);
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}