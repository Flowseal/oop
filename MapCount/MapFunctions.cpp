#include "MapFunctions.h"
// TODO rename map

void AddWordsFromStream(std::map<std::string, int>& countMap, std::istream& stream)
{
	if (!stream)
		throw std::runtime_error("Can't read from stream!");

	std::string word;
	while (stream >> word)
	{
		countMap[word]++;
	}

	if (stream.bad())
		throw std::runtime_error("Error reading from stream!");
}

void PrintWordsCount(const std::map<std::string, int>& countMap, std::ostream& stream)
{
	if (!stream)
		throw std::runtime_error("Cant write to stream!");

	for (auto& it : countMap)
	{
		stream << it.first << " -> " << it.second << std::endl;
	}

	if (!stream.flush())
		throw std::runtime_error("Error writing to stream!");
}
