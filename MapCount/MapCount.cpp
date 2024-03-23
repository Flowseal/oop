#include "MapFunctions.h"

int main()
{
	try
	{
		std::unordered_map<std::string, int> map;

	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}