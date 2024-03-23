#include "HtmlFunctions.h"

int main()
{
	std::string inputString;
	std::getline(std::cin, inputString);

	std::cout << HtmlDecode(inputString);
}