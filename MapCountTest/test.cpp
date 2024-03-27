#include "pch.h"
#include "../MapCount/MapFunctions.cpp"

TEST(AddWordsFromStreamTest, Empty)
{
	std::unordered_map<std::string, int> countMap;
	std::stringstream ss;
	AddWordsFromStream(countMap, ss);

	std::unordered_map<std::string, int> expectCountMap;
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, NoWords)
{
	std::unordered_map<std::string, int> countMap;
	std::stringstream ss;
	ss << "\t \n   ";
	AddWordsFromStream(countMap, ss);

	std::unordered_map<std::string, int> expectCountMap;
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, SingleWord)
{
	std::unordered_map<std::string, int> countMap;
	std::stringstream ss;
	ss << "Hello";
	AddWordsFromStream(countMap, ss);

	std::unordered_map<std::string, int> expectCountMap{
		{ "Hello", 1 }
	};
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, Mixed)
{
	std::unordered_map<std::string, int> countMap;
	std::stringstream ss;
	ss << "Hello \t World \t Привет \n  Привет  Мир World 1234 5";
	AddWordsFromStream(countMap, ss);

	std::unordered_map<std::string, int> expectCountMap{
		{ "Hello", 1 },
		{ "World", 2 },
		{ "Привет", 2 },
		{ "Мир", 1 },
		{ "1234", 1 },
		{ "5", 1 },
	};
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(PrintWordsCountTest, Empty)
{
	std::unordered_map<std::string, int> countMap;
	std::ostringstream output;
	PrintWordsCount(countMap, output);

	std::ostringstream expectedOutput;
	EXPECT_EQ(output.str(), expectedOutput.str());
}

TEST(PrintWordsCountTest, SingleWord)
{
	std::unordered_map<std::string, int> countMap{
		{ "Hello", 1 }
	};
	std::ostringstream output;
	PrintWordsCount(countMap, output);

	std::ostringstream expectedOutput;
	expectedOutput << "Hello -> 1" << std::endl;
	EXPECT_EQ(output.str(), expectedOutput.str());
}

TEST(PrintWordsCountTest, Mixed)
{
	std::unordered_map<std::string, int> countMap{
		{ "Hello", 1 },
		{ "Мир", 1 },
		{ "2024", 2 }
	};
	std::ostringstream output;
	PrintWordsCount(countMap, output);

	std::ostringstream expectedOutput;
	expectedOutput << "Hello -> 1" << std::endl;
	expectedOutput << "Мир -> 1" << std::endl;
	expectedOutput << "2024 -> 2" << std::endl;
	EXPECT_EQ(output.str(), expectedOutput.str());
}

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}