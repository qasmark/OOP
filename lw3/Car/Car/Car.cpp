#include "Car.h"

static constexpr int MIN_GEAR = -1;
static constexpr int MAX_GEAR = 5;
static constexpr int MAX_SPEED = 150;

struct GearLimitSpeed
{
		int lowerLimit;
		int upperLimit;
};

const std::map<int, GearLimitSpeed> SpeedLimitsInGears =
{
		{ -1, {0, 20} },
		{ 0, {0, MAX_SPEED} },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, MAX_SPEED } },
};

bool Car::IsTurnedOn()
{
		return m_isEngineOn;
}

bool Car::TurnOffEngine()
{
		if (!m_isEngineOn || m_gear != 0 || m_speed != 0)
		{
			return false;
		}

		m_isEngineOn = false;
		return true;
}

bool Car::TurnOnEngine()
{
		if (m_isEngineOn)
		{
			return false;
		}

		m_isEngineOn = true;
		return true;
}

int Car::GetGear()
{
		return m_gear;
}

int Car::GetSpeed()
{
		return std::abs(m_speed); // можно ли убрать abs 
}

Car::MoveDirection Car::GetDirection()
{
		if (m_speed > 0 && m_gear == -1)
		{
			return MoveDirection::BACKWARD;
		}
		if (m_speed > 0 && m_gear == 0 && Car::MoveDirection::BACKWARD == MoveDirection::BACKWARD)
		{
			return MoveDirection::BACKWARD;
		}
		if (m_speed > 0)
		{
			return MoveDirection::FORWARD;
		}
		if (m_speed == 0)
		{
			return MoveDirection::STAY;
		}

		return MoveDirection::BACKWARD;
}

bool Car::SetGear(int gear)
	{
		if (!m_isEngineOn)
		{
			return false;
		}

		if (gear < MIN_GEAR || gear > MAX_GEAR)
		{
			return false;
		}

		if ((m_gear > 0 && gear < 0) && (m_gear < 0 && gear > 0))
		{
			return false;
		}

		auto const limits = SpeedLimitsInGears.at(gear);
		if (std::abs(m_speed) < limits.lowerLimit || std::abs(m_speed) > limits.upperLimit)
		{
			return false;
		}

		m_gear = gear;
		return true;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (m_gear == 0 && speed > std::abs(m_speed))
	{
		return false;
	}

	auto const limits = SpeedLimitsInGears.at(m_gear);
	if (speed < limits.lowerLimit || speed > limits.upperLimit)
	{
		return false;
	}

	if (m_speed < 0)
	{
		m_speed = std::abs(speed);
		return true;
	}

	m_speed = m_gear == -1 ? -speed : speed;
	return true;
}


