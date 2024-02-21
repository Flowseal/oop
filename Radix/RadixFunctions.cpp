#include "RadixFunctions.h"
#include "stdafx.h"

std::string IntToString(int n, int radix, bool& wasError)
{
	static const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPRSTUVWXYZ";
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
		// Индекс символа с конца
		int back_index = str.length() - 1 - i;

		// Переводим символ std::string в char и получаем его номер в системе кодировки
		char ch = str[i];
		int ch_value;

		if (ch >= '0' && ch <= '9')
		{
			ch_value = (ch - '0') * std::pow(radix, back_index);
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch_value = (ch - 'A' + 10) * std::pow(radix, back_index);
		}
		else
		{
			wasError = true;
			return 0;
		}

		if (ch_value > radix)
		{
			wasError = true;
			return 0;
		}
		result += ch_value;
	}

	return result;
}

std::string ConvertToRadix(const int sourceNotation, const int destinationNotation, const std::string& value)
{
	bool wasError = false;
	bool isNegative = value[0] == '-';

	int decimalValue = StringToInt(isNegative ? value.substr(1) : value, sourceNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting value to decimal system");
	}

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