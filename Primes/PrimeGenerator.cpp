#include "PrimeGenerator.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
		return std::set<int>{};

	std::vector<bool> prime(upperBound + 1, true);
	std::vector<int> result{ 2 };

	for (int i = 4; i <= upperBound; i += 2)
	{
		prime[i] = false;
	}

	int p = 3;
	for (; p * p <= upperBound; p += 2)
	{
		if (prime[p])
		{
			result.push_back(p);
			for (int i = p * p; i <= upperBound; i += 2 * p)
			{
				prime[i] = false;
			}
		}
	}

	for (; p <= upperBound; p += 2)
	{
		if (prime[p])
		{
			result.push_back(p);
		}
	}

	return std::set<int>(result.begin(), result.end());
}