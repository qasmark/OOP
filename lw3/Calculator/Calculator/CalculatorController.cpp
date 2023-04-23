#include "CalculatorController.h"

CalculatorController::CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_inputStream(input)
	, m_outputStream(output)
	, m_actionMap({
		  { "var", bind(&CalculatorController::DefineVariable, this, std::placeholders::_1) },
		  { "let", bind(&CalculatorController::AssignVariable, this, std::placeholders::_1) },
		  { "fn", bind(&CalculatorController::AssignFunction, this, std::placeholders::_1) },
		  { "print", bind(&CalculatorController::Print, this, std::placeholders::_1) },
		  { "printvars", bind(&CalculatorController::PrintVariables, this, std::placeholders::_1) },
		  { "printfns", bind(&CalculatorController::PrintFunctions, this, std::placeholders::_1) },
	  })
{
}

bool CalculatorController::HandleCommand()
{
	std::string commandLine;

	std::getline(m_inputStream, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	m_outputStream << std::fixed << std::setprecision(2);

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CalculatorController::DefineVariable(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage: var <name of variable>" << std::endl;
		return false;
	}

	std::string variableName;
	args >> variableName;

	if (m_calculator.DefineVariable(variableName))
	{
		m_outputStream << "Variable <" << variableName << "> successfully created" << std::endl;
		return true;
	}
	m_outputStream << "Can not create variable <" << variableName << ">:" << std::endl
				   << "- Variable must starts with letter or _ and contains only letters, numbers, _." << std::endl
				   << "- Maybe this variable is already existing." << std::endl;

	return false;
}

bool CalculatorController::AssignVariable(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage: let <name of variable> = <value>/<another variable>" << std::endl;
		return false;
	}

	std::string variableName;
	args >> variableName;

	std::string valueOrAnotherVariable;
	args >> valueOrAnotherVariable;
	args >> valueOrAnotherVariable;

	Value value;

	try
	{
		value = std::stod(valueOrAnotherVariable);
		if (m_calculator.AssignVariable(variableName, value))
		{
			m_outputStream << "Variable <" << variableName << "> successfully assigned with value "
						   << "<" << value << ">" << std::endl;
			return true;
		}
	}
	catch (...)
	{
		if (m_calculator.AssignVariable(variableName, valueOrAnotherVariable))
		{
			m_outputStream << "Variable <" << variableName << "> successfully assigned with variable "
						   << "<" << valueOrAnotherVariable << ">" << std::endl;
			return true;
		}
	}

	m_outputStream << "Can not assing variable <" << variableName << ">:" << std::endl
				   << "- Variable must starts with letter or _ and contains only letters, numbers, _." << std::endl
				   << "- If you assing variable with another, another one must exists" << std::endl;

	return false;
}

bool CalculatorController::AssignFunction(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage: fn <name of function> = <another function>" << std::endl
					   << "or fn <name of function> = <identifier1> <operation> <identifier2>" << std::endl;
		return false;
	}

	Identifier functionName;
	args >> functionName;

	Identifier anotherFunctionOrFirstIdentifier;
	args >> anotherFunctionOrFirstIdentifier;
	args >> anotherFunctionOrFirstIdentifier;

	bool isAssigningWithFunction = false;
	if (args.eof())
	{
		isAssigningWithFunction = true;
		if (m_calculator.AssignFunction(functionName, anotherFunctionOrFirstIdentifier))
		{
			m_outputStream << "Function <" << functionName << "> successfully assigned with function "
						   << "<" << anotherFunctionOrFirstIdentifier << ">" << std::endl;
			return true;
		}
	}
	else
	{
		char operation;
		args >> operation;
		Identifier anotherIdentifier;
		args >> anotherIdentifier;
		if (m_calculator.AssignFunction(functionName, Expression{ anotherFunctionOrFirstIdentifier, CharToOperation(operation), anotherIdentifier }))
		{
			m_outputStream << "Function <" << functionName << "> successfully assigned with expression "
						   << "<" << anotherFunctionOrFirstIdentifier <<  operation << anotherIdentifier << ">" << std::endl;
			return true;
		}
	}
	m_outputStream << "Can not assing function <" << functionName << ">:" << std::endl
				   << "Correct usage: fn <name of function> = <another function>" << std::endl
				   << "or fn <name of function> = <identifier1> <operation> <identifier2>" << std::endl;

	return false;
}

bool CalculatorController::Print(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage: print <name of function>/<name of variable>" << std::endl;
		return false;
	}

	Identifier identifierName;
	args >> identifierName;

	if (m_calculator.IsFunctionExist(identifierName))
	{
		m_outputStream << m_calculator.GetFunctionValue(identifierName).value() << std::endl;
		return true;
	}

	if (m_calculator.IsVariableExist(identifierName))
	{
		m_outputStream << m_calculator.GetVariableValue(identifierName).value() << std::endl;
		return true;
	}

	m_outputStream << "This variable/function doesn't exist" << std::endl;
	return false;
}

bool CalculatorController::PrintVariables(std::istream& args)
{
	Variables allVariables = m_calculator.GetAllVariables();
	for (auto& it : allVariables)
	{
		m_outputStream << it.first << ":" << it.second << std::endl;
	}
	return true;
}

bool CalculatorController::PrintFunctions(std::istream& args)
{
	Functions allFunctions = m_calculator.GetAllFunctions();
	for (auto& it : allFunctions)
	{
		m_outputStream << it.first << ":" << m_calculator.GetExpressionValue(it.second) << std::endl;
	}
	return true;
}

Operation CalculatorController::CharToOperation(char op) const
{
	switch (op)
	{
	case '+':
		return Operation::ADDITION;
	case '-':
		return Operation::SUBTRACTION;
	case '*':
		return Operation::MULTIPLICATION;
	case '/':
		return Operation::DIVISION;
	default:
		return Operation::NONE;
	}
}
