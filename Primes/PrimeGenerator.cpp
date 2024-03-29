#include "PrimeGenerator.h"
const int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
		return std::set<int>{};

	if (upperBound > MAX_UPPER_BOUND)
		throw std::runtime_error("upperBound is greater than maximum bound (100000000)");

	std::vector<bool> prime(upperBound + 1, true);
	prime[0] = false;
	prime[1] = false;

	for (int i = 4; i <= upperBound; i += 2)
	{
		prime[i] = false;
	}

	int p = 3;
	for (; p * p <= upperBound; p += 2)
	{
		if (prime[p])
		{
			for (int i = p * p; i <= upperBound; i += 2 * p)
			{
				prime[i] = false;
			}
		}
	}

	std::set<int> result;
	for (int i = 0; i < prime.size(); i++)
	{
		if (prime[i])
		{
			result.insert(i);
		}
	}

	return result;
}