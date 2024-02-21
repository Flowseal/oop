#pragma once
#include <string>

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);
std::string ConvertToRadix(const int sourceNotation, const int destinationNotation, const std::string& value);