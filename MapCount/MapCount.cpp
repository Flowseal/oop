#include "MapFunctions.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::unordered_map<std::string, int> map;
		AddWordsFromStream(map, std::cin);
		PrintWordsCount(map, std::cout);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}