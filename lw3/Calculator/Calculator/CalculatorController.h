#pragma once

#include "Calculator.h"
#include <iostream>
#include <functional>
#include <sstream>
#include <iomanip>

class CalculatorController
{
public:
	CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();


private:
	bool DefineVariable(std::istream& args);
	bool AssignVariable(std::istream& args);
	bool AssignFunction(std::istream& args);
	bool Print(std::istream& args);
	bool PrintVariables(std::istream& args);
	bool PrintFunctions(std::istream& args);

	Calculator& m_calculator;
	std::istream& m_inputStream;
	std::ostream& m_outputStream;

	Operation CharToOperation(char op) const;
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;
};
