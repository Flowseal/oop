#include "Car.h"
#include <sstream>

void ProcessCommand(Car& car, const std::string& command, const std::string& strArgument)
{
	int argument = 0;
	if (strArgument != "")
	{
		try
		{
			argument = std::stoi(strArgument);
		}
		catch (...)
		{
			std::cout << "Argument should be int value" << std::endl;
			return;
		}
	}
	

	if (command == "Help")
	{
		std::cout << "Info -> get current car's state" << std::endl;
		std::cout << "EngineOn -> turn engine on" << std::endl;
		std::cout << "EngineOff -> turn engine off" << std::endl;
		std::cout << "SetGear -> change car's gear (-1 to 5)" << std::endl;
		std::cout << "SetSpeed -> change car's speed" << std::endl;
	}
	else if (command == "Info")
	{
		std::cout << "Engine status: " << (car.GetEngineStatus() ? "ON" : "OFF") << std::endl; 

		switch (car.GetDirection())
		{
		case MoveDirection::FORWARD:
			std::cout << "Move direction: forward" << std::endl;
		case MoveDirection::BACKWARD:
			std::cout << "Move direction: backward" << std::endl;
		case MoveDirection::STANDING:
			std::cout << "Move direction: standing still" << std::endl;
		}
		
		std::cout << "Speed: " << car.GetSpeed() << std::endl;
		std::cout << "Gear: " << car.GetGear() << std::endl;
	}
	else if (command == "EngineOn")
	{
		car.TurnOnEngine();
	}
	else if (command == "EngineOff")
	{
		car.TurnOffEngine();
	}
	else if (command == "SetGear")
	{
		car.SetGear(argument);
	}
	else if (command == "SetSpeed")
	{
		car.SetSpeed(argument);
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

int main()
{
	Car car;
	std::string line, command;

	while (getline(std::cin, line))
	{
		std::string argument = "";
		std::stringstream ss(line);

		if (!(ss >> command))
		{
			std::cout << "No command found" << std::endl;
			continue;
		}

		ss >> argument;
		ProcessCommand(car, command, argument);
	}
}