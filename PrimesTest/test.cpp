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

TEST(GeneratePrimeNumbersSetTest, MaxUpperBound)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100000000);
	EXPECT_EQ(primes.size(), 5761455);
}

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}