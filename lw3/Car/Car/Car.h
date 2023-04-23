#pragma once

#include <iostream>
#include <map>

class Car
{
public:
		enum class MoveDirection
		{
			BACKWARD,
			STAY,
			FORWARD,
		};

		bool IsTurnedOn();
		bool TurnOnEngine();
		bool TurnOffEngine();

		MoveDirection GetDirection();

		int GetSpeed();
		int GetGear();

		bool SetSpeed(int speed);
		bool SetGear(int gear);
private:
		bool m_isEngineOn = false;
		int m_gear = 0;
		int m_speed = 0;
};

