#pragma once

#include "Car.h"
#include <functional>
#include <sstream>
#include <string>

class ControllerCar
{
public:
		ControllerCar(std::istream& input, std::ostream& output, Car& car);
		void ControlCar();
private:
		static std::string ConvertMoveDirectionToString(Car::MoveDirection);
		

		void SetSpeed(int speed);
		void SetGear(int gear);
		void EngineOff();
		void EngineOn();
		void PrintInfo();
		void Help();


		enum class CommandType
		{
			DEFAULT,
			HELP,
			INFO,
			EXIT,
			ENGINE_ON,
			ENGINE_OFF,
			SET_GEAR,
			SET_SPEED,

		};

		struct Command
		{
			CommandType type;
			int argument;
		};

		using CommandHandler = std::function<void(int argument)>;

		Command ReadCommand();
		static CommandType ParseCommandType(const std::string& command);
		CommandHandler GetHandlerForCommand(CommandType command);

		std::istream& m_input;
		std::ostream& m_output;
		Car& m_car;
};

