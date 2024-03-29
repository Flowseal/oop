#pragma once
#include "stdafx.h"

void AddWordsFromStream(std::map<std::string, int>& countMap, std::istream& stream);
void PrintWordsCount(const std::map<std::string, int>& countMap, std::ostream& stream);
