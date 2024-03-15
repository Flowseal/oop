#pragma once
#include "stdafx.h"

std::vector<double> ReadNumbersFromStream(std::istream& input);
void MultiplyVectorOnMin(std::vector<double>& numbers);
void OutputVectorToStream(const std::vector<double>& numbers, std::ostream& output);