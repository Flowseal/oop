#include "VectorFunctions.h"

std::vector<double> ReadNumbersFromStream(std::istream& input)
{
	if (!input)
	{
		throw std::runtime_error("Error reading input!");
	}

	std::vector<double> numbers;

	double number;
	while (input >> number)
		numbers.push_back(number);

	if (input.bad())
	{
		throw std::runtime_error("Error reading input!");
	}

	if (!input.eof())
	{
		throw std::runtime_error("Error reading input!");
	}

	return numbers;
}

void MultiplyVectorOnMin(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double minNumber = *std::min_element(numbers.begin(), numbers.end());
	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [&minNumber](auto& c) { return c * minNumber; });
}

void OutputVectorToStream(const std::vector<double>& numbers, std::ostream& output)
{
	if (!output)
	{
		throw std::runtime_error("Error writing to output!");
	}

	if (numbers.empty())
	{
		return;
	}

	std::copy(numbers.begin(), numbers.end() - 1, std::ostream_iterator<double>(output, " "));
	output << *(numbers.end() - 1);

	if (!output.flush())
	{
		throw std::runtime_error("Error writing to output!");
	}
}
