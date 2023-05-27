#pragma once
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include "CCanvas.h"

class ShapesHandler
{
public:
	ShapesHandler(std::istream& input, std::ostream& output);

	bool HandleCommand() const;
	void PrintMaxAreaShape() const;
	void PrintMinPerimeterShape() const;
	void DrawShaped(unsigned width, unsigned height, const std::string& windowTitle) const;

private:
	struct ArgsLine
	{
		CPoint startPoint;
		CPoint endPoint;
		HexColor outlineColor;
	};

	struct ArgsTriangle
	{
		CPoint vertex1;
		CPoint vertex2;
		CPoint vertex3;
		HexColor fillColor;
		HexColor outlineColor;
	};

	struct ArgsRectangle
	{
		CPoint leftTopPoint;
		CPoint rightBottomPoint;
		HexColor fillColor;
		HexColor outlineColor;
	};

	struct ArgsCircle
	{
		CPoint centerPoint;
		double radius;
		HexColor fillColor;
		HexColor outlineColor;
	};

	bool CreateLine(std::istream& args);
	bool CreateCircle(std::istream& args);
	bool CreateRectangle(std::istream& args);
	bool CreateTriangle(std::istream& args);
	bool PrintAllShapes(std::istream& args);
	bool Help(std::istream& args);

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	ActionMap m_actionMap;
	std::istream& m_inputStream;
	std::ostream& m_outputStream;

	using IShapeSmartPointer = std::unique_ptr<IShape>;
	std::vector<IShapeSmartPointer> m_shapes;
};