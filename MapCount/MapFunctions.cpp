#include "MapFunctions.h"

void AddWord(std::unordered_map<std::string, int>& map, const std::string& word)
{
	std::string word_lowercase = word;
	std::transform(word_lowercase.begin(), word_lowercase.end(), word_lowercase.begin(),
		[](unsigned char c) { return std::tolower(c); });

	map.try_emplace(word_lowercase, 0);
	auto it = map.find(word_lowercase);
	it->second += 1;
}

void AddWordsFromStream(std::unordered_map<std::string, int> map, std::istream& stream)
{
	if (!stream)
		throw std::runtime_error("Can't read from stream!");

	std::string word;
	while (stream >> word)
	{
		AddWord(map, word);
	}
}

void PrintWordsCount(const std::unordered_map<std::string, int>& map, std::ostream& stream)
{
	for (auto it = map.begin(); it != map.end(); it++)
	{
		stream << it->first << " -> " << it->second << std::endl;
	}
}
