#include "stdafx.h"
#include "RadixFunctions.h"

std::string IntToString(int n, int radix)
{
	static const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool negative = n < 0;

	std::string result;
	int reminder;

	while (n)
	{
		reminder = abs(n % radix);
		n /= radix;

		result = alphabet[reminder] + result;
	}

	if (negative)
		result.insert(0, "-");

	return result;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	bool isNegative = !str.empty() && str[0] == '-';

	if (str.length() == isNegative)
	{
		wasError = true;
		return 0;
	}

	int result = 0;

	for (size_t i = isNegative; i < str.length(); i++)
	{
		char ch = str[i];
		int ch_value = -1;

		if (ch >= '0' && ch <= '9')
		{
			ch_value = (ch - '0');
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch_value = (ch - 'A' + 10);
		}

		if (ch_value >= radix || ch_value == -1)
		{
			wasError = true;
			return 0;
		}

		if (isNegative)
			ch_value *= -1;

		// Overflow и Underflow проверка
		if (!isNegative && result > (INT_MAX - ch_value) / radix
			|| isNegative && result < (INT_MIN - ch_value) / radix)
		{
			wasError = true;
			return 0;
		}

		result = result * radix + ch_value;
	}

	return result;
}

std::string ConvertToRadix(const int sourceNotation, const int destinationNotation, const std::string& value)
{
	bool wasError = false;

	// Конвертируем value в int в десятичной системе
	int decimalValue = StringToInt(value, sourceNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting value to decimal system");
	}

	// Ковертируем
	std::string result = IntToString(decimalValue, destinationNotation);
	if (wasError)
	{
		throw std::runtime_error("Error on converting decimal value to destination notation");
	}

	return result;
}