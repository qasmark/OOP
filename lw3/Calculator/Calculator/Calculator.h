#pragma once
#include <map>
#include <optional>
#include <string>
#include <regex>
#include <limits>

enum class Operation
{
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	NONE
};

using Identifier = std::string;
using Value = double; // переместить в класс

struct Expression
{
	Identifier firstOperand;
	Operation operation;
	Identifier secondOperand;
};

using Variables = std::map<Identifier, Value>;
using Functions = std::map<Identifier, Expression>;

const Value NAN_VALUE = std::numeric_limits<Value>::quiet_NaN();


class Calculator
{
public:
	Calculator();
	bool DefineVariable(Identifier const& identifier);

	bool AssignVariable(Identifier const& identifier, Value const& value);
	bool AssignVariable(Identifier const& identifier1, Identifier const& identifier2);
	bool AssignFunction(Identifier const& identifier, Expression const& expression);
	bool AssignFunction(Identifier const& identifier1, Identifier const& identifier2);

	Variables GetAllVariables() const;
	Functions GetAllFunctions() const; 

	std::optional<Value> GetVariableValue(Identifier const& identifier) const;
	std::optional<Value> GetFunctionValue(Identifier const& identifier);

	// mb private
	std::optional<Expression> GetFunctionExpression(Identifier const& Expression) const;
	Value GetExpressionValue(Expression const& expression) const;
	bool IsIdentifierCorrect(Identifier const& identifier) const;
	bool IsIdentifierExist(Identifier const& identifier) const;
	bool IsFunctionExist(Identifier const& identifier) const;
	bool IsVariableExist(Identifier const& identifier) const;

private:
	Value GetExpressionValueRecursive(Identifier const& identifier) const;
	Functions m_functions;
	Variables m_variables;
};
