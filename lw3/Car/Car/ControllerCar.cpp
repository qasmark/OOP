#include "ControllerCar.h"

ControllerCar::ControllerCar(std::istream& input, std::ostream& output, Car& car)
		: m_input(input),
		m_output(output),
		m_car(car)
{

}
		  
void ControllerCar::ControlCar()
{
	bool finished = false;

	while (!finished)
	{
		auto const command = ReadCommand();
		switch (command.type)
		{
		case CommandType::HELP:
		case CommandType::INFO:
		case CommandType::ENGINE_ON:
		case CommandType::ENGINE_OFF:
		case CommandType::SET_GEAR:
		case CommandType::SET_SPEED:
			GetHandlerForCommand(command.type)(command.argument);
			break;
		case CommandType::EXIT:
			finished = true;
			m_output << "\n";
			break;
		default:
			break;
		}
	}
}

ControllerCar::CommandType ControllerCar::ParseCommandType(const std::string& command)
{
	if (command == "help")
	{
		return CommandType::HELP;
	}
	else if (command == "info")
	{
		return CommandType::INFO;
	}
	else if (command == "exit")
	{
		return CommandType::EXIT;
	}
	else if (command == "EngineOn")
	{
		return CommandType::ENGINE_ON;
	}
	else if (command == "EngineOff")
	{
		return CommandType::ENGINE_OFF;
	}
	else if (command == "SetGear")
	{
		return CommandType::SET_GEAR;
	}
	else if (command == "SetSpeed")
	{
		return CommandType::SET_SPEED;
	}

	throw std::invalid_argument("invalid command");
}

ControllerCar::CommandHandler ControllerCar::GetHandlerForCommand(ControllerCar::CommandType command)
{
	switch (command)
	{
	case CommandType::HELP:
		return [this](int) {
			Help();
		};
	case CommandType::INFO:
		return [this](int) {
			PrintInfo();
		};
	case CommandType::ENGINE_ON:
		return [this](int) {
			EngineOn();
		};
	case CommandType::ENGINE_OFF:
		return [this](int) {
			EngineOff();
		};
	case CommandType::SET_GEAR:
		return [this](int gear) {
			SetGear(gear);
		};
	case CommandType::SET_SPEED:
		return [this](int speed) {
			SetSpeed(speed);
		};
	default:
		throw std::invalid_argument("no handler for command");
	}
}

ControllerCar::Command ControllerCar::ReadCommand()
{
	std::string userInput;
	int argument;
	std::getline(m_input, userInput);
	if (m_input.eof())
	{
		return  { ControllerCar::CommandType::EXIT, 0 };
	}
	std::stringstream input(userInput);
	Command command;
	CommandType type = CommandType::DEFAULT;
	std::string commandTypeStr;

	try
	{
		std::getline(input, commandTypeStr, ' ');
		if (!(input >> argument))
		{
			argument = 0;
		}
		type = ParseCommandType(commandTypeStr);
			
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
		return {};
	}

	return {
		command.type = type,
		command.argument = argument,
	};
}

std::string ControllerCar::ConvertMoveDirectionToString(Car::MoveDirection moveDirection)
{
		switch (moveDirection)
		{
		case Car::MoveDirection::BACKWARD:
				return "backward";
		case Car::MoveDirection::STAY:
				return "stay";
		case Car::MoveDirection::FORWARD:
				return "forward";
		default:
				return {};
		}
}

void ControllerCar::Help()
{
	m_output << "help - show this message\n"
		"info - print car status\n"
		"exit - stop the program\n"
		"EngineOn - start the car engine\n"
		"EngineOff - stop the car engine\n"
		"SetGear <gear>	- change car gear\n"
		"SetSpeed <speed> - change car speed\n";
}

void ControllerCar::SetSpeed(int speed)
{
		if (m_car.SetSpeed(speed))
		{
				m_output << "Speed has been set to " << speed << "\n";
				return;
		}

		m_output << "Failed to set set speed by next value: " << speed << "\n";
}

void ControllerCar::SetGear(int gear)
{
		if (m_car.SetGear(gear))
		{
				m_output << "Gear has been set to " << gear << "\n";
				return;
		}
		m_output << "Failed to set set speed by next value: " << gear << "\n";
}

void ControllerCar::EngineOn()
{
		if (m_car.TurnOnEngine())
		{
				m_output << "Engine has been turned on\n";
				return;
		}

		m_output << "Failed to turn on the engine\n";
}

void ControllerCar::EngineOff()
{
		if (m_car.TurnOffEngine())
		{
			m_output << "Engine has been turned off\n";
			return;
		}

		m_output << "Failed to turn off the engine\n";
}

void ControllerCar::PrintInfo()
{
	m_output << "Car status:\n"
		<< "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << '\n'
		<< "Direction: " << ConvertMoveDirectionToString(m_car.GetDirection()) << '\n'
		<< "Speed: " << m_car.GetSpeed() << '\n'
		<< "Gear: " << m_car.GetGear() << '\n';
}	