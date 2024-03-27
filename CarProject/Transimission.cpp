#include "Transmission.h"

bool ValidateGearChange(int gear, int nextGear, int speed);

bool Transmission::IsGearSpeedValid(int gear, int speed, const std::map<int, std::pair<int, int>>& gearSpeeds)
{
	std::pair<int, int> speedRange = (*gearSpeeds.find(gear)).second;

	if (speed < speedRange.first || speed > speedRange.second)
		return false;

	return true;
}

bool Transmission::SetGear(int gear, int currentSpeed, const std::map<int, std::pair<int, int>>& gearSpeeds)
{
	if (gear == m_gear)
		return true;

	if (gearSpeeds.find(gear) == gearSpeeds.end())
	{
		std::cout << "Can't set gear: Undefined gear number" << std::endl;
		return false;
	}

	if (!IsGearSpeedValid(gear, currentSpeed, gearSpeeds))
	{
		std::cout << "Can't set gear: speed is not in the gear's range" << std::endl;
		return false;
	}
	
	if (m_waitUntilStop && currentSpeed != 0)
	{
		std::cout << "Can't set gear: wait until Car's stop" << std::endl;
		return false;
	}

	if (!ValidateGearChange(m_gear, gear, currentSpeed))
		return false;
	
	if (m_gear == -1 && gear == 0)
		m_waitUntilStop = true;
	else
		m_waitUntilStop = false;

	m_gear = gear;
	return true;
}

bool ValidateGearChange(int gear, int nextGear, int speed)
{
	if (nextGear == -1 && speed > 0)
	{
		std::cout << "Can't set backward gear: car should be staying" << std::endl;
		return false;
	}

	if (gear == -1 && nextGear > 0 && speed != 0)
	{
		std::cout << "Can't set forward gear: car should be staying" << std::endl;
		return false;
	}

	return true;
}