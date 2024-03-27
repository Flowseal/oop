#include "Car.h"

bool Car::TurnOnEngine()
{
	m_engineTurned = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_engineTurned)
		return true;

	if (m_speed != 0 || m_transimission.GetGear() != 0)
		return false;

	m_engineTurned = false;
	return true;
}

bool Car::SetGear(int gear)
{
	if (!m_engineTurned)
		return gear == 0;

	return m_transimission.SetGear(gear, m_speed, m_gearSpeeds);
}

bool Car::SetSpeed(int speed)
{
	if (speed == m_speed)
		return true;

	if (speed < 0)
	{
		std::cout << "Speed can't be negatvie value" << std::endl;
		return false;
	}

	if (!Transmission::IsGearSpeedValid(m_transimission.GetGear(), speed, m_gearSpeeds))
	{
		std::cout << "Speed is not in the gear's range" << std::endl;
		return false;
	}

	if (speed > m_speed && m_transimission.GetGear() == 0)
	{
		std::cout << "Speed can't be increased on neutral gear" << std::endl;
		return false;
	}

	m_speed = speed;
	return true;
}

MoveDirection Car::GetDirection() const
{
	int gear = m_transimission.GetGear();

	if (m_speed == 0)
		return MoveDirection::STANDING;

	if (gear == -1)
		return MoveDirection::BACKWARD;

	if (gear > 0)
		return MoveDirection::FORWARD;
}