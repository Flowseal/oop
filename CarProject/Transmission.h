#pragma once
#include "stdafx.h"

class Transmission
{
public:
	static bool IsGearSpeedValid(int gear, int speed, const std::map<int, std::pair<int, int>>& gearSpeeds);
	int GetGear() const { return m_gear; }
	bool SetGear(int gear, int currentSpeed, const std::map<int, std::pair<int, int>>& gearSpeeds);

private:
	int m_gear = 0;
	bool m_waitUntilStop = false;
};