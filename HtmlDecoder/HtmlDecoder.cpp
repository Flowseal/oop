#include "HtmlFunctions.h"
// TODO add while getline

int main()
{
	std::string inputString;
	while (std::getline(std::cin, inputString))
	{
		std::cout << HtmlDecode(inputString);
	}
}