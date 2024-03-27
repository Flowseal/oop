#pragma once
#include "stdafx.h"

void AddWord(std::unordered_map<std::string, int>& map, const std::string& word);
void AddWordsFromStream(std::unordered_map<std::string, int>& map, std::istream& stream);
void PrintWordsCount(const std::unordered_map<std::string, int>& map, std::ostream& stream);
