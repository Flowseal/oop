#include "VectorFunctions.h"

int main(int argc, char* argv[])
{
	try
	{
		std::vector<double> numbers = ReadNumbersFromStream(std::cin);
		MultiplyVectorOnMin(numbers);
		std::sort(numbers.begin(), numbers.end());
		OutputVectorToStream(numbers, std::cout);
	}
	catch (const std::runtime_error& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	catch (const std::exception& exception)
	{
		std::cout << "Unexpected error: " << exception.what() << std::endl;
		return 1;
	}

	return 0;
}