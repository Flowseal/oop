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
}

bool Car::SetGear(int gear)
{
	
}

bool Car::SetSpeed(int speed)
{

}

MoveDirection Car::GetDirection() const
{
	if (m_gear == 0)
		return MoveDirection::STANDING;

	if (m_gear == -1)
		return MoveDirection::BACKWARD;

	if (m_gear > 0)
		return MoveDirection::FORWARD;
}