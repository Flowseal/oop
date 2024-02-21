#include "RadixFunctions.h"
#include "stdafx.h"

std::string IntToString(int n, int radix, bool& wasError)
{
	static const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;
	int reminder;

	while (n)
	{
		reminder = n % radix;
		n /= radix;

		if (reminder >= radix)
		{
			wasError = true;
		}

		result = alphabet[reminder] + result;
	}

	return result;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	if (str.empty())
	{
		wasError = true;
		return 0;
	}

	int result = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		// Индекс символа с конца, который будем исп. в качестве степени системы счисления
		int back_index = str.length() - 1 - i;

		char ch = str[i];
		int ch_value;

		if (ch >= '0' && ch <= '9')
		{
			ch_value = (ch - '0');
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch_value = (ch - 'A' + 10);
		}
		else
		{
			wasError = true;
			return 0;
		}

		if (ch_value >= radix)
		{
			wasError = true;
			return 0;
		}

		result += ch_value * std::pow(radix, back_index);
	}

	return result;
}

std::string ConvertToRadix(const int sourceNotation, const int destinationNotation, const std::string& value)
{
	bool wasError = false;
	bool isNegative = value[0] == '-';

	// Конвертируем value в int в десятичной системе
	int decimalValue = StringToInt(isNegative ? value.substr(1) : value, sourceNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting value to decimal system");
	}

	// Ковертируем 
	std::string result = IntToString(decimalValue, destinationNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting decimal value to destination notation");
	}

	if (isNegative)
	{
		result.insert(0, "-");
	}
	return result;
}