#pragma once
#include "stdafx.h"

enum class MoveDirection
{
	FORWARD = 0,
	BACKWARD,
	STANDING
};

class Car
{
public:
	bool GetEngineStatus() const { return m_engineTurned; }
	bool TurnOnEngine();
	bool TurnOffEngine();

	int GetGear() const { return m_gear; }
	bool SetGear(int gear);

	int GetSpeed() const { return m_speed; }
	bool SetSpeed(int speed);

	MoveDirection GetDirection() const;
private:
	bool m_engineTurned = false;
	int m_gear = 0;
	int m_speed = 0;

	std::map<int, std::pair<int, int>> m_gearSpeeds
	{
		{ -1, { 0, 20 }},
		{ 0, { 0, 0 }},
		{ 1, { 0, 30 }},
		{ 2, { 20, 50 }},
		{ 3, { 30, 60 }},
		{ 4, { 40, 90 }},
		{ 5, { 50, 150 }}
	};
};