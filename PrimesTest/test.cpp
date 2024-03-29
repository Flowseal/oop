#include "pch.h"
#include "../Primes/PrimeGenerator.cpp"

TEST(GeneratePrimeNumbersSetTest, NegativeUpperBound)
{
	std::set<int> primes = GeneratePrimeNumbersSet(-1);
	EXPECT_EQ(primes.size(), 0);
}

TEST(GeneratePrimeNumbersSetTest, ZeroBound)
{
	std::set<int> primes = GeneratePrimeNumbersSet(0);
	EXPECT_EQ(primes.size(), 0);
}

TEST(GeneratePrimeNumbersSetTest, ZeroPrimes)
{
	std::set<int> primes = GeneratePrimeNumbersSet(1);
	EXPECT_EQ(primes.size(), 0);
}

TEST(GeneratePrimeNumbersSetTest, SinglePrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(2);
	EXPECT_EQ(primes.size(), 1);
}

TEST(GeneratePrimeNumbersSetTest, AveragePrimes)
{
	std::set<int> primes = GeneratePrimeNumbersSet(7044);
	EXPECT_EQ(primes.size(), 906);
}

// TODO check if set equals
// TODO add test if upperbound not prime

TEST(GeneratePrimeNumbersSetTest, SmallUpperBoundNotPrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(18);
	std::set<int> expectedPrimes{
		2, 3, 5, 7, 11, 13, 17
	};
	EXPECT_EQ(primes, expectedPrimes);
}

TEST(GeneratePrimeNumbersSetTest, SmallUpperBoundPrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(19);
	std::set<int> expectedPrimes{
		2, 3, 5, 7, 11, 13, 17, 19
	};
	EXPECT_EQ(primes, expectedPrimes);
}

TEST(GeneratePrimeNumbersSetTest, MaxUpperBound)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100000000);
	EXPECT_EQ(primes.size(), 5761455);
}

TEST(GeneratePrimeNumbersSetTest, UpperBoundIsPrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(99999989);
	EXPECT_EQ(primes.size(), 5761455);
}

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}