#include "MapFunctions.h"

void AddWord(std::unordered_map<std::string, int>& map, const std::string& word)
{
	map.try_emplace(word, 0);
	auto it = map.find(word);
	it->second += 1;
}

void AddWordsFromStream(std::unordered_map<std::string, int>& map, std::istream& stream)
{
	if (!stream)
		throw std::runtime_error("Can't read from stream!");

	std::string word;
	while (stream >> word)
	{
		AddWord(map, word);
	}

	if (stream.bad())
		throw std::runtime_error("Error reading from stream!");
}

void PrintWordsCount(const std::unordered_map<std::string, int>& map, std::ostream& stream)
{
	if (!stream)
		throw std::runtime_error("Cant write to stream!");

	for (auto it = map.begin(); it != map.end(); it++)
	{
		stream << it->first << " -> " << it->second << std::endl;
	}

	if (!stream.flush())
		throw std::runtime_error("Error writing to stream!");
}
