#include "pch.h"
#include "../Vector2/VectorFunctions.cpp"

TEST(ReadNumbersTest, WrongInputData)
{
	std::stringstream ss;
	ss << "2 Wrong 6";
	EXPECT_THROW(ReadNumbersFromStream(ss), std::runtime_error);
}

TEST(ReadNumbersTest, EmptyInput)
{
	std::stringstream ss;
	std::vector<double> numbers = ReadNumbersFromStream(ss);
	EXPECT_EQ(numbers.size(), 0);
}

TEST(ReadNumbersTest, CorrectInputData)
{
	std::stringstream ss;
	ss << "2.4 8 0 2";

	std::vector<double> expected_numbers{ 2.4, 8, 0, 2 };
	std::vector<double> actual_numbers = ReadNumbersFromStream(ss);

	EXPECT_EQ(expected_numbers, actual_numbers);
}

TEST(MultiplyVectorOnMinTest, ZeroMultiplication)
{
	std::vector<double> numbers{ 2.4, 8, 0, 2 };
	MultiplyVectorOnMin(numbers);

	std::vector<double> expected_numbers{ 0, 0, 0, 0 };
	EXPECT_EQ(numbers, expected_numbers);
}

TEST(MultiplyVectorOnMinTest, NegativeMultiplication)
{
	std::vector<double> numbers{ 2.4, 8, -2, 2 };
	MultiplyVectorOnMin(numbers);

	std::vector<double> expected_numbers{ -4.8, -16, 4, -4 };
	EXPECT_EQ(numbers, expected_numbers);
}

TEST(MultiplyVectorOnMinTest, PositiveMultiplication)
{
	std::vector<double> numbers{ 2.4, 8, 0.5, 2 };
	MultiplyVectorOnMin(numbers);

	std::vector<double> expected_numbers{ 1.2, 4, 0.25, 1 };
	EXPECT_EQ(numbers, expected_numbers);
}

TEST(MultiplyVectorOnMinTest, EmptyVector)
{
	std::vector<double> numbers{ };
	MultiplyVectorOnMin(numbers);

	std::vector<double> expected_numbers{ };
	EXPECT_EQ(numbers, expected_numbers);
}

TEST(OutputVectorTest, EmptyVector)
{
	std::stringstream ss;
	std::vector<double> numbers{};
	OutputVectorToStream(numbers, ss);

	EXPECT_EQ(ss.str(), "");
}

TEST(OutputVectorTest, NotEmptyVector)
{
	std::stringstream ss;
	std::vector<double> numbers{0.5, -2, 5};
	OutputVectorToStream(numbers, ss);

	EXPECT_EQ(ss.str(), "0.500 -2.000 5.000");
}

TEST(MultiplyAndOutputTest, PrecisionTest)
{
	std::stringstream ss;
	std::vector<double> numbers{ 0.999,	1.5, 1 };
	MultiplyVectorOnMin(numbers);
	OutputVectorToStream(numbers, ss);

	EXPECT_EQ(ss.str(), "0.998 1.498 0.999");
}


GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}