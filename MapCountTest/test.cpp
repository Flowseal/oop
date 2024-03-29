#include "pch.h"
#include "../MapCount/MapFunctions.cpp"

// TODO change to eng tests

TEST(AddWordsFromStreamTest, Empty)
{
	std::map<std::string, int> countMap;
	std::stringstream ss;
	AddWordsFromStream(countMap, ss);

	std::map<std::string, int> expectCountMap;
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, NoWords)
{
	std::map<std::string, int> countMap;
	std::stringstream ss;
	ss << "\t \n   ";
	AddWordsFromStream(countMap, ss);

	std::map<std::string, int> expectCountMap;
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, SingleWord)
{
	std::map<std::string, int> countMap;
	std::stringstream ss;
	ss << "Hello";
	AddWordsFromStream(countMap, ss);

	std::map<std::string, int> expectCountMap{
		{ "Hello", 1 }
	};
	EXPECT_EQ(countMap, expectCountMap);
}

// TODO add tests to symbols like '(+,..;&*^%
TEST(AddWordsFromStreamTest, SpecialSymbols)
{
	std::map<std::string, int> countMap;
	std::stringstream ss;
	ss << "Hello%%. World*&^! ,/@$ ( (";
	AddWordsFromStream(countMap, ss);

	std::map<std::string, int> expectCountMap{
		{ "Hello%%.", 1 },
		{ "World*&^!", 1 },
		{ ",/@$", 1 },
		{ "(", 2 }
	};
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(AddWordsFromStreamTest, Mixed)
{
	std::map<std::string, int> countMap;
	std::stringstream ss;
	ss << "Hello \t World \t \n 5 World 1234 5";
	AddWordsFromStream(countMap, ss);

	std::map<std::string, int> expectCountMap{
		{ "Hello", 1 },
		{ "World", 2 },
		{ "5", 2 },
		{ "1234", 1 },
	};
	EXPECT_EQ(countMap, expectCountMap);
}

TEST(PrintWordsCountTest, Empty)
{
	std::map<std::string, int> countMap;
	std::ostringstream output;
	PrintWordsCount(countMap, output);

	std::ostringstream expectedOutput;
	EXPECT_EQ(output.str(), expectedOutput.str());
}

TEST(PrintWordsCountTest, SingleWord)
{
	std::map<std::string, int> countMap{
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
	std::map<std::string, int> countMap{
		{ "2024", 1 },
		{ "Hello", 1 },
		{ "World$$", 2 },
	};
	std::ostringstream output;
	PrintWordsCount(countMap, output);

	std::ostringstream expectedOutput;
	expectedOutput << "2024 -> 1" << std::endl;
	expectedOutput << "Hello -> 1" << std::endl;
	expectedOutput << "World$$ -> 2" << std::endl;
	EXPECT_EQ(output.str(), expectedOutput.str());
}

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}