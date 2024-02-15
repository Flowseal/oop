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
	int result = 0;
	const char* char_array = str.c_str();

	for (size_t i = 0; i < str.length(); i++)
	{
		// Индекс символа с конца
		int back_index = str.length() - 1 - i;

		// Переводим символ std::string в char и получаем его номер в системе кодировки
		char ch = char_array[i];
		int ch_code = int(ch);
		int ch_value;

		if (ch_code >= '0' && ch_code <= '9')
		{
			ch_value = (ch_code - '0') * std::pow(radix, back_index);
		}
		else if (ch_code >= 'A' && ch_code <= 'Z')
		{
			ch_value = (ch_code - 'A' + 10) * std::pow(radix, back_index);
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

void ConvertArgumentNotationsToInt(int& sourceNotation, int& destinationNotation,
	const std::string& rawSourceNotation, const std::string& rawDestinationNotation)
{
	try
	{
		sourceNotation = std::stoi(rawSourceNotation);
		destinationNotation = std::stoi(rawDestinationNotation);
	}
	catch (...)
	{
		throw std::runtime_error("Error on reading notation argument");
	}

	if (sourceNotation < 2 || sourceNotation > 36)
	{
		throw std::runtime_error("Error: sourceNotation must be in [2; 36]");
	}
	if (destinationNotation < 2 || destinationNotation > 36)
	{
		throw std::runtime_error("Error: destinationNotation must be in [2; 36]");
	}
}

void ConvertNumberToRadix(const std::string& rawSourceNotation,
	const std::string& rawDestinationNotation, const std::string& value)
{
	int sourceNotation, destinationNotation;
	ConvertArgumentNotationsToInt(sourceNotation, destinationNotation,
		rawSourceNotation, rawDestinationNotation);

	if (value.length() == 0)
	{
		throw std::runtime_error("Error on reading value argument");
	}

	bool wasError = false;
	bool hasMinus = value[0] == '-';

	int decimalValue = StringToInt(hasMinus ? value.substr(1) : value, sourceNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting value to decimal system");
	}

	std::string result = IntToString(decimalValue, destinationNotation, wasError);
	if (wasError)
	{
		throw std::runtime_error("Error on converting decimal value to destination notation");
	}

	if (hasMinus)
	{
		result = "-" + result;
	}
	std::cout << result << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	try
	{
		ConvertNumberToRadix(argv[1], argv[2], argv[3]);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
