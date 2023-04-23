#include "Calculator.h"

Calculator::Calculator()
	: m_functions({})
	, m_variables({})
{
}

bool Calculator::DefineVariable(Identifier const& identifier)
{
	if (!IsIdentifierCorrect(identifier) || IsIdentifierExist(identifier))
	{
		return false;
	}

	m_variables.emplace(identifier, NAN_VALUE);
	return true;
}

bool Calculator::AssignVariable(Identifier const& identifier, Value const& value)
{
	if (IsIdentifierExist(identifier))
	{
		m_variables[identifier] = value;
		return true;
	}

	if (IsIdentifierCorrect(identifier))
	{
		DefineVariable(identifier);
		m_variables[identifier] = value;
		return true;
	}

	return false;
}

bool Calculator::AssignVariable(Identifier const& identifier1, Identifier const& identifier2)
{
	if (!IsIdentifierExist(identifier2))
	{
		return false;
	}

	if (!IsIdentifierExist(identifier1))
	{
		if (!IsIdentifierCorrect(identifier1))
		{
			return false;
		}
		DefineVariable(identifier1);
	}

	if (IsFunctionExist(identifier2))
	{
		auto it = m_functions.find(identifier2);
		m_variables[identifier1] = GetExpressionValue(it->second);
		return true;
	}

	auto it = m_variables.find(identifier2);
	m_variables[identifier1] = it->second;
	return true;
}

std::optional<Value> Calculator::GetVariableValue(Identifier const& identifier) const
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	auto variable = m_variables.find(identifier);
	return variable->second;
}

Variables Calculator::GetAllVariables() const
{
	return m_variables;
}

bool Calculator::IsIdentifierCorrect(Identifier const& identifier) const
{
	std::smatch result;
	std::regex regex("([a-zA-Z_][a-zA-Z0-9_]*)");
	if (!regex_match(identifier, result, regex))
	{
		return false;
	}
	return true;
}

bool Calculator::IsIdentifierExist(Identifier const& identifier) const
{
	if (!IsFunctionExist(identifier) && !IsVariableExist(identifier))
	{
		return false;
	}
	return true;
}

bool Calculator::IsFunctionExist(Identifier const& identifier) const
{
	if (m_functions.find(identifier) == m_functions.end())
	{
		return false;
	}
	return true;
}

bool Calculator::IsVariableExist(Identifier const& identifier) const
{
	if (m_variables.find(identifier) == m_variables.end())
	{
		return false;
	}
	return true;
}



bool Calculator::AssignFunction(Identifier const& identifier, Expression const& expression)
{
	if (!IsIdentifierCorrect(identifier))
	{
		return false;
	}

	if (IsIdentifierExist(identifier))
	{
		return false;
	}

	if (!IsIdentifierExist(expression.firstOperand) || !IsIdentifierExist(expression.secondOperand))
	{
		return false;
	}

	m_functions.emplace(identifier, expression);
	return true;
}

bool Calculator::AssignFunction(Identifier const& identifier1, Identifier const& identifier2)
{
	if (IsIdentifierExist(identifier1) || !IsIdentifierExist(identifier2))
	{
		return false;
	}

	if (!IsIdentifierCorrect(identifier1))
	{
		return false;
	}

	m_functions.emplace(identifier1, Expression{ identifier2, Operation::NONE, identifier2 });
	return true;
}

std::optional<Expression> Calculator::GetFunctionExpression(Identifier const& identifier) const
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	auto expression = m_functions.find(identifier);
	return expression->second;
}

Value Calculator::GetExpressionValue(Expression const& expression) const
{
	Value firstOperandValue = GetExpressionValueRecursive(expression.firstOperand);
	Value secondOperandValue = GetExpressionValueRecursive(expression.secondOperand);

	switch (expression.operation)
	{
	case Operation::ADDITION:
		return firstOperandValue + secondOperandValue;
	case Operation::SUBTRACTION:
		return firstOperandValue - secondOperandValue;
	case Operation::MULTIPLICATION:
		return firstOperandValue * secondOperandValue;
	case Operation::DIVISION:
		return firstOperandValue / secondOperandValue;
	default:
		return firstOperandValue;
	}
}

Value Calculator::GetExpressionValueRecursive(Identifier const& identifier) const
{
	if (IsVariableExist(identifier))
	{
		return GetVariableValue(identifier).value();
	}
	else
	{
		Expression tempExpression = m_functions.find(identifier)->second;
		return GetExpressionValue(tempExpression);
	}
}

std::optional<Value> Calculator::GetFunctionValue(Identifier const& identifier)
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	Expression functionExpression = GetFunctionExpression(identifier).value();
	return GetExpressionValue(functionExpression);
}

Functions Calculator::GetAllFunctions() const
{
	return m_functions;
}
