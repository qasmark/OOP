#define CATCH_CONFIG_MAIN
#include "../../../lw2/catch2/catch.hpp"
#include "../Calculator/Calculator.h"

SCENARIO("Testing isIdentifierCorrect")
{
	Calculator calculator;
	WHEN("Identifier is empty")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier is digit")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "1";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier is letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "a";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with digit")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "1amount";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "amount1";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with Capital letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "Amount1";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier doesn't contain digit")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "amount";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
}

SCENARIO("Testing IsIdentifierExist")
{

	WHEN("Identifier doesn't exist")
	{
		Calculator calculator;
		THEN("Return FALSE = identifier is not occupied")
		{
			Identifier identifier = "amount";
			REQUIRE(!calculator.IsIdentifierExist(identifier));
		}
	}
	WHEN("Identifier exists")
	{
		Calculator calculator;
		Identifier identifier = "amount";
		calculator.DefineVariable(identifier);
		THEN("Return TRUE = identifier is occupied")
		{
			Identifier identifierCopy = "amount";
			REQUIRE(calculator.IsIdentifierExist(identifierCopy));
		}
	}
	WHEN("Identifier exists")
	{
		Calculator calculator;
		Identifier identifier = "amount";
		calculator.DefineVariable(identifier);

		Identifier functionIdentifier = "fn1";
		calculator.AssignFunction(functionIdentifier, identifier);
		THEN("Return TRUE = identifier is occupied")
		{
			Identifier functionIdentifierCopy = "amount";
			calculator.AssignFunction(functionIdentifierCopy, identifier);
		}
	}
}

SCENARIO("Testing DefineVariable")
{
	WHEN("Identifier is not occupied and correctly written")
	{
		Calculator calculator;
		THEN("Identifier is defined")
		{
			Identifier identifier = "excellentIdentifierName";
			REQUIRE(calculator.DefineVariable(identifier));
		}
	}
	WHEN("Identifier is occupied and correctly written")
	{
		Calculator calculator;
		THEN("Identifier is not defined")
		{
			Identifier identifier1 = "excellentIdentifierName";
			REQUIRE(calculator.DefineVariable(identifier1));

			Identifier identifier2 = "excellentIdentifierName";
			REQUIRE(!calculator.DefineVariable(identifier2));
		}
	}
	WHEN("Identifier is not occupied but incorrectly written")
	{
		Calculator calculator;
		THEN("Identifier is not defined")
		{
			Identifier identifier1 = "1Terrible(Identifier=Name";
			REQUIRE(!calculator.DefineVariable(identifier1));
		}
	}
}

SCENARIO("Testing GetVariableValue")
{
	WHEN("Variable doesn't exist")
	{
		Calculator calculator;
		THEN("Return FALSE, value = std::nullopt")
		{
			Identifier identifier = "x";
			REQUIRE(!calculator.GetVariableValue(identifier));
			REQUIRE(calculator.GetVariableValue(identifier) == std::nullopt);
		}
	}
	WHEN("Variable exist, but its value is NAN")
	{
		Calculator calculator;
		THEN("Returned Value is NAN")
		{
			Identifier identifier = "x";
			REQUIRE(calculator.DefineVariable(identifier));

			REQUIRE(isnan(calculator.GetVariableValue(identifier).value()));
		}
	}
	WHEN("Variable exist, and has value")
	{
		Calculator calculator;
		THEN("Returned Value is 777.888")
		{
			Identifier identifier = "x";
			Value value = 777.888;
			REQUIRE(calculator.AssignVariable(identifier, value));

			REQUIRE(calculator.GetVariableValue(identifier).value() == value);
		}
	}
}

SCENARIO("Testing AssignVariable with value")
{
	WHEN("Variable doesn't exist")
	{
		Calculator calculator;
		THEN("New variable has been created and assinged with the value")
		{
			Identifier identifier = "x";
			Value value = 1.245;
			REQUIRE(!calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.AssignVariable(identifier, value));
			REQUIRE(calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.GetVariableValue(identifier).value() == value);
		}
	}
	WHEN("Variable exist")
	{
		Calculator calculator;
		THEN("Variable assinged with the value")
		{
			Identifier identifier = "x";
			Value value = 1.245;
			REQUIRE(calculator.DefineVariable(identifier));
			REQUIRE(calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.AssignVariable(identifier, value));
			REQUIRE(calculator.IsIdentifierExist(identifier));
			REQUIRE(calculator.GetVariableValue(identifier).value() == value);
		}
	}
}

SCENARIO("Testing AssignVariable with another variable")
{
	WHEN("Both variables don't exist")
	{
		Calculator calculator;
		THEN("Return FALSE, no define")
		{
			Identifier identifier1 = "x";
			Identifier identifier2 = "y";
			REQUIRE(!calculator.IsIdentifierExist(identifier1));
			REQUIRE(!calculator.IsIdentifierExist(identifier2));

			REQUIRE(!calculator.AssignVariable(identifier1, identifier2));
		}
	}
	WHEN("First variable exists, but second doesn't")
	{
		Calculator calculator;
		THEN("Return FALSE, no define")
		{
			Identifier identifier1 = "x";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			Identifier identifier2 = "y";
			REQUIRE(!calculator.IsIdentifierExist(identifier2));

			REQUIRE(!calculator.AssignVariable(identifier1, identifier2));
		}
	}
	WHEN("First variable doesn't exist, but second does")
	{
		Calculator calculator;
		THEN("First variable is now existing and its value = second variable's value")
		{
			Identifier identifier1 = "x";
			REQUIRE(!calculator.IsIdentifierExist(identifier1));
			Identifier identifier2 = "y";
			REQUIRE(calculator.DefineVariable(identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier2));
			Value value2 = 5.53241;
			REQUIRE(calculator.AssignVariable(identifier2, value2));

			REQUIRE(calculator.AssignVariable(identifier1, identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			REQUIRE(calculator.GetVariableValue(identifier1).value() == value2);
		}
	}
	WHEN("First variable exist and so does second one")
	{
		Calculator calculator;
		THEN("First variable's value is now second variable's value")
		{
			Identifier identifier1 = "x";
			Value value1 = 1415.53241;
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			REQUIRE(calculator.AssignVariable(identifier1, value1));
			REQUIRE(calculator.GetVariableValue(identifier1).value() == value1);

			Identifier identifier2 = "y";
			Value value2 = 5.53241;
			REQUIRE(calculator.DefineVariable(identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier2));
			REQUIRE(calculator.AssignVariable(identifier2, value2));
			REQUIRE(calculator.GetVariableValue(identifier2).value() == value2);

			REQUIRE(calculator.AssignVariable(identifier1, identifier2));
			REQUIRE(calculator.GetVariableValue(identifier2).value() == value2);
		}
	}
}

SCENARIO("Testing AssignVariable with function")
{
	WHEN("Variable exist")
	{
		Calculator calculator;
		THEN("Variable assinged with the value")
		{
			Identifier x = "x";
			Value xValue = 2;
			REQUIRE(calculator.DefineVariable(x));
			REQUIRE(calculator.IsIdentifierExist(x));
			REQUIRE(calculator.AssignVariable(x, xValue));
			Identifier functionIdentifier = "fn1";
			Expression expression{ x, Operation::MULTIPLICATION, x };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));

			Identifier y = "y";
			REQUIRE(calculator.AssignVariable(y, functionIdentifier));
			REQUIRE(calculator.GetVariableValue(y) == xValue * xValue);
		}
	}
}

SCENARIO("Testing GetAllVariables")
{
	WHEN("No vars defined")
	{
		Calculator calculator;
		THEN("Result is empty map")
		{
			REQUIRE(calculator.GetAllVariables().empty());
		}
	}
	WHEN("Some vars defined")
	{
		Calculator calculator;
		THEN("Result is map with defined vars")
		{
			Identifier identifier1 = "var1";
			Value value1 = 9014.21214;
			Identifier identifier2 = "var2";
			Value value2 = 124.124;
			REQUIRE(calculator.AssignVariable(identifier1, value1));
			REQUIRE(calculator.AssignVariable(identifier2, value2));

			REQUIRE(calculator.GetAllVariables() == Variables{ { identifier1, value1 }, { identifier2, value2 } });
		}
	}
}

SCENARIO("Testing AssingFunction with expression")
{
	WHEN("Identifier is incorrect")
	{
		Calculator calculator;
		THEN("Function won't be assigned")
		{
			Identifier functionIdentifier = "1";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(!calculator.AssignFunction(functionIdentifier, expression));
		}
	}
	WHEN("Identifier is correct and doesn't exist")
	{
		Calculator calculator;
		THEN("Function will be assigned")
		{
			Identifier functionIdentifier = "functionId";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));
		}
	}
	WHEN("Identifier is correct and already exist")
	{
		Calculator calculator;
		THEN("Function won't be assigned again")
		{
			Identifier functionIdentifier = "functionId";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));

			REQUIRE(!calculator.AssignFunction(functionIdentifier, expression));
		}
	}
}

SCENARIO("Testin AssignFunction With function")
{
	WHEN("Identifier1 and identifier2 is already existing")
	{
		Calculator calculator;
		THEN("Function won't be assigned again")
		{
			Identifier functionIdentifier = "functionId";
			Identifier functionIdentifier2 = "functionId2";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));
			REQUIRE(calculator.AssignFunction(functionIdentifier2, expression));

			REQUIRE(!calculator.AssignFunction(functionIdentifier, functionIdentifier2));
		}
	}
	WHEN("Identifier1 is already existing and identifier2 doesn't")
	{
		Calculator calculator;
		THEN("Function won't be assigned again")
		{
			Identifier functionIdentifier = "functionId";
			Identifier functionIdentifier2 = "functionId2";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));

			REQUIRE(!calculator.AssignFunction(functionIdentifier, functionIdentifier2));
		}
	}
	WHEN("Identifier1 doesn't exist and identifier2 doesn't")
	{
		Calculator calculator;
		THEN("Function won't be assigned again")
		{
			Identifier functionIdentifier = "functionId";
			Identifier functionIdentifier2 = "functionId2";

			REQUIRE(!calculator.AssignFunction(functionIdentifier, functionIdentifier2));
		}
	}
	WHEN("Identifier1 doesn't exist but identifier2 doesn")
	{
		Calculator calculator;
		THEN("Function won't be assigned again")
		{
			Identifier functionIdentifier2 = "functionId2";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier2, expression));

			Identifier functionIdentifier = "functionId";
			REQUIRE(calculator.AssignFunction(functionIdentifier, functionIdentifier2));
		}
	}
}
SCENARIO("Testin AssignFunction With variable")
{
	WHEN("")
	{
		Calculator calculator;
		Identifier var1 = "var1";
		Value var1Value = 3.842;
		Identifier function1 = "function1";
		REQUIRE(calculator.AssignVariable(var1, var1Value));
		REQUIRE(calculator.AssignFunction(function1, var1));

		REQUIRE(calculator.GetFunctionValue(function1) == var1Value);

	}
}

SCENARIO("Testing GetFunctionExpression")
{
	WHEN("Identifier exists")
	{
		Calculator calculator;
		THEN("Return Expression")
		{
			Identifier functionIdentifier = "functionId";
			Identifier identifier1 = "var1";
			Identifier identifier2 = "var2";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.DefineVariable(identifier2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));

			REQUIRE(calculator.GetFunctionExpression(functionIdentifier).value().firstOperand == expression.firstOperand);
			REQUIRE(calculator.GetFunctionExpression(functionIdentifier).value().operation == expression.operation);
			REQUIRE(calculator.GetFunctionExpression(functionIdentifier).value().secondOperand == expression.secondOperand);
		}
	}

	WHEN("Identifier doesn't exist")
	{
		Calculator calculator;
		THEN("Doesn't return Expression")
		{
			Identifier functionIdentifier = "functionId";
			REQUIRE(calculator.GetFunctionExpression(functionIdentifier) == std::nullopt);
		}
	}
}
SCENARIO("Testing GetExpressionValue")
{
	Calculator calculator;
	Identifier identifier1 = "var1";
	Identifier identifier2 = "var2";
	Value identifierValue1 = 2532.512;
	Value identifierValue2 = 100;

	WHEN("operation +")
	{
		THEN("Return correct value")
		{
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));
			REQUIRE(calculator.AssignVariable(identifier2, identifierValue2));
			Expression expression = { identifier1, Operation::ADDITION, identifier2 };
			REQUIRE(calculator.GetExpressionValue(expression) == identifierValue1 + identifierValue2);
		}
	}
	WHEN("operation -")
	{
		THEN("Return correct value")
		{
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));
			REQUIRE(calculator.AssignVariable(identifier2, identifierValue2));
			Expression expression = { identifier1, Operation::SUBTRACTION, identifier2 };
			REQUIRE(calculator.GetExpressionValue(expression) == identifierValue1 - identifierValue2);
		}
	}
	WHEN("operation *")
	{
		THEN("Return correct value")
		{
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));
			REQUIRE(calculator.AssignVariable(identifier2, identifierValue2));
			Expression expression = { identifier1, Operation::MULTIPLICATION, identifier2 };
			REQUIRE(calculator.GetExpressionValue(expression) == identifierValue1 * identifierValue2);
		}
	}
	WHEN("operation /")
	{
		THEN("Return correct value")
		{
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));
			REQUIRE(calculator.AssignVariable(identifier2, identifierValue2));
			Expression expression = { identifier1, Operation::DIVISION, identifier2 };
			REQUIRE(calculator.GetExpressionValue(expression) == identifierValue1 / identifierValue2);
		}
	}

	WHEN("operation NONE")
	{
		THEN("Return correct value")
		{
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));

			Expression expression = { identifier1, Operation::NONE, identifier1 };
			REQUIRE(calculator.GetExpressionValue(expression) == identifierValue1);
		}
	}

	WHEN("one of the operands's value is nan")
	{
		THEN("Return nan")
		{
			Identifier idNan = "idNan";
			REQUIRE(calculator.AssignVariable(identifier1, identifierValue1));
			REQUIRE(calculator.DefineVariable(idNan));

			Expression expression = { identifier1, Operation::ADDITION, idNan };
			REQUIRE(isnan(calculator.GetExpressionValue(expression)));
		}
	}
}

SCENARIO("Testing GetFunctionValue")
{
	WHEN("Function doesn't exist")
	{
		Calculator calculator;
		THEN("return std::nullopt")
		{
			Identifier functionIdentifier = "XplusY";
			REQUIRE(!calculator.GetFunctionValue(functionIdentifier));
		}
	}
	WHEN("Function exists")
	{
		Calculator calculator;
		THEN("return value")
		{
			Identifier functionIdentifier = "XplusY";

			Identifier variableIdentifier1 = "var1";
			Identifier variableIdentifier2 = "var2";
			Value variableIdentifierValue1 = 2532.512;
			Value variableIdentifierValue2 = 100;
			REQUIRE(calculator.AssignVariable(variableIdentifier1, variableIdentifierValue1));
			REQUIRE(calculator.AssignVariable(variableIdentifier2, variableIdentifierValue2));
			Expression expression = { variableIdentifier1, Operation::ADDITION, variableIdentifier2 };
			REQUIRE(calculator.AssignFunction(functionIdentifier, expression));

			REQUIRE(calculator.GetFunctionValue(functionIdentifier).value() == variableIdentifierValue1 + variableIdentifierValue2);
		}
	}
}

SCENARIO("Testing calculator")
{
	WHEN("Defining, assigning, and getting values of variables")
	{
		Calculator calculator;
		Identifier x = "x";
		REQUIRE(calculator.DefineVariable(x));
		REQUIRE(isnan(calculator.GetVariableValue(x).value()));
		Value var1Value = 42;
		REQUIRE(calculator.AssignVariable(x, var1Value));
		REQUIRE(calculator.GetVariableValue(x).value() == var1Value);
		Identifier y = "y";
		REQUIRE(calculator.AssignVariable(y, x));
		REQUIRE(calculator.GetVariableValue(y).value() == var1Value);
		REQUIRE(calculator.GetAllVariables() == Variables{ { x, var1Value }, { y, var1Value } });
	}
	WHEN("Assigning functions")
	{
		Calculator calculator;
		Identifier x = "x";
		Identifier y = "y";
		REQUIRE(calculator.DefineVariable(x));
		REQUIRE(calculator.DefineVariable(y));
		Identifier function1 = "XplusY";
		Expression expression1 = { x, Operation::ADDITION, y };
		REQUIRE(calculator.AssignFunction(function1, expression1));
		REQUIRE(isnan(calculator.GetFunctionValue(function1).value()));
		Value var1Value = 3;
		Value var2Value = 4;
		REQUIRE(calculator.AssignVariable(x, var1Value));
		REQUIRE(calculator.AssignVariable(y, var2Value));
		REQUIRE(calculator.GetFunctionValue(function1).value() == var1Value + var2Value);
		Value var1ValueNew = 10;
		REQUIRE(calculator.AssignVariable(x, var1ValueNew));
		REQUIRE(calculator.GetFunctionValue(function1).value() == var1ValueNew + var2Value);

		Identifier z = "z";
		Value var3Value = 3.5;
		REQUIRE(calculator.AssignVariable(z, var3Value));
		Identifier function2 = "XplusYdivZ";
		Expression expression2 = { function1, Operation::DIVISION, z };
		REQUIRE(calculator.AssignFunction(function2, expression2));

		REQUIRE(calculator.GetFunctionValue(function2).value() == (var1ValueNew + var2Value) / var3Value);

		REQUIRE(calculator.GetAllFunctions().size() == 2);
	}

	WHEN("Finding area of circle")
	{
		Calculator calculator;

		Identifier radius = "radius";
		REQUIRE(calculator.DefineVariable(radius));
		Identifier pi = "pi";
		Value piValue = 3.14159265;
		REQUIRE(calculator.AssignVariable(pi, piValue));

		Identifier radiusSquared = "radiusSquared";
		Expression expression1 = { radius, Operation::MULTIPLICATION, radius };
		REQUIRE(calculator.AssignFunction(radiusSquared, expression1));

		Identifier circleArea = "circleArea";
		Expression expression2 = { pi, Operation::MULTIPLICATION, radiusSquared };
		REQUIRE(calculator.AssignFunction(circleArea, expression2));

		Value radiusValue = 10;
		REQUIRE(calculator.AssignVariable(radius, radiusValue));

		REQUIRE(calculator.GetFunctionValue(circleArea).value() == (radiusValue * radiusValue) * piValue);
	}
	WHEN("Fibonacci test")
	{
		Calculator calculator;
		Identifier v0 = "v0";
		Value v0Value = 0;
		Identifier v1 = "v1";
		Value v1Value = 1;

		REQUIRE(calculator.AssignVariable(v0, v0Value));
		REQUIRE(calculator.AssignVariable(v1, v1Value));

		Identifier fib0 = "fib0";
		REQUIRE(calculator.AssignFunction(fib0, v0));
		Identifier fib1 = "fib1";
		REQUIRE(calculator.AssignFunction(fib1, v1));

		Identifier fib2 = "fib2";
		Expression fib2Expression{ fib0, Operation::ADDITION, fib1 };
		REQUIRE(calculator.AssignFunction(fib2, fib2Expression));

		Identifier fib3 = "fib3";
		Expression fib3Expression{ fib2, Operation::ADDITION, fib1 };
		REQUIRE(calculator.AssignFunction(fib3, fib3Expression));

		Identifier fib4 = "fib4";
		Expression fib4Expression{ fib3, Operation::ADDITION, fib2 };
		REQUIRE(calculator.AssignFunction(fib4, fib4Expression));

		Identifier fib5 = "fib5";
		Expression fib5Expression{ fib4, Operation::ADDITION, fib3 };
		REQUIRE(calculator.AssignFunction(fib5, fib5Expression));

		Identifier fib6 = "fib6";
		Expression fib6Expression{ fib5, Operation::ADDITION, fib4 };
		REQUIRE(calculator.AssignFunction(fib6, fib6Expression));

		REQUIRE(calculator.GetFunctionValue(fib6).value() == 8);
	}
}
