#include "PrimeGenerator.h"

struct Args
{
	int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Wrong arguments count! Usage: Primes.exe <upperBound>");
	}
	
	int upperBound = 0;
	try
	{
		upperBound = std::stoi(argv[1]);
	}
	catch (...)
	{
		throw std::invalid_argument("Upper bound should be integer");
	}

	Args args;
	args.upperBound = upperBound;
	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		std::cout << GeneratePrimeNumbersSet(args->upperBound).size() << std::endl;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	catch (const std::runtime_error& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << "Unexpected error: " << exception.what() << std::endl;
	}	
}