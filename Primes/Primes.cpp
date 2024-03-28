#include "PrimeGenerator.h"

int main()
{
	int upperBound = 0;
	std::cin >> upperBound;
	std::cout << GeneratePrimeNumbersSet(upperBound).size();
}