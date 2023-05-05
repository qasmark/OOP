#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/CCanvas.h"
#include "../Shapes/Point/CPoint.h"
#include "../Shapes/Shapes/LineSegment/CLineSegment.h"
#include "../Shapes/Shapes/SolidShapes/Circle/CCircle.h"
#include "../Shapes/Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "../Shapes/Shapes/SolidShapes/Triangle/CTriangle.h"
#include "../Shapes/ShapesController.h"

SCENARIO("Testing CPoint")
{
	WHEN("Init CPoint with coordinates")
	{
		THEN("CPoint is correctly inited")
		{
			const CPoint point(12.3, 45.67);
			REQUIRE(point.GetPointX() == 12.3);
			REQUIRE(point.GetPointY() == 45.67);
		}
	}
	WHEN("GetDistance between two points")
	{
		THEN("Distance between two points equals correctDistance")
		{
			const CPoint point1(2, -5);
			const CPoint point2(-4, 3);
			const double correctDistance = sqrt(pow((point2.GetPointX() - point1.GetPointX()), 2) + pow((point2.GetPointY() - point1.GetPointY()), 2));
			REQUIRE(CPoint::GetDistance(point1, point2) == correctDistance);
		}
	}
	WHEN("Comparison identical CPoints")
	{
		THEN("Point are equal")
		{
			const CPoint point1(12.3, 45.67);
			const CPoint point2(12.3, 45.67);
			REQUIRE(point1 == point2);
		}
	}
	WHEN("Comparison non-identical CPoints")
	{
		THEN("Point are not equal")
		{
			const CPoint point1(12.3, 45.67);
			const CPoint point2(12.3, 45.68);
			REQUIRE(!(point1 == point2));
		}
	}
}

SCENARIO("Testing CTriangle")
{
	const CPoint triangleVertex1 = { 0, 0 };
	const CPoint triangleVertex2 = { 3, 0 };
	const CPoint triangleVertex3 = { 2, 2 };
	const HexColor triangleFillColor = 0xff00ff;
	const HexColor triangleOutlineColor = 0x00ff00;

	const CTriangle triangle(triangleVertex1, triangleVertex2, triangleVertex3, triangleFillColor, triangleOutlineColor);
	WHEN("Testing GetFillColor")
	{
		REQUIRE(triangle.GetFillColor() == triangleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(triangle.GetOutlineColor() == triangleOutlineColor);
	}

	const double distanceVertex12 = CPoint::GetDistance(triangleVertex1, triangleVertex2);
	const double distanceVertex13 = CPoint::GetDistance(triangleVertex1, triangleVertex3);
	const double distanceVertex23 = CPoint::GetDistance(triangleVertex2, triangleVertex3);

	WHEN("Testing GetPerimeter")
	{
		const double correctTrianglePerimeter = distanceVertex12 + distanceVertex13 + distanceVertex23;
		REQUIRE(triangle.GetPerimeter() == correctTrianglePerimeter);
	}
	WHEN("Testing GetArea")
	{
		const double halfPerimeter = triangle.GetPerimeter() / 2;
		const double correctTriangleArea = sqrt(halfPerimeter * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12));
		REQUIRE(triangle.GetArea() == correctTriangleArea);
	}
}

SCENARIO("Testing CRectangleee")
{
	const CPoint rectangleLeftTopPoint = { 0, 10 };
	const CPoint rectangleRightBottomPoint = { 10, 0 };

	const HexColor rectangleFillColor = 0xff00ff;
	const HexColor rectangleOutlineColor = 0x00ff00;

	const CRectangle rectangle(rectangleLeftTopPoint, rectangleRightBottomPoint, rectangleFillColor, rectangleOutlineColor);

	WHEN("Testing GetFillColor")
	{
		REQUIRE(rectangle.GetFillColor() == rectangleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(rectangle.GetOutlineColor() == rectangleOutlineColor);
	}

	const double rectangleCorrectWidth = rectangleRightBottomPoint.GetPointX() - rectangleLeftTopPoint.GetPointX();
	const double rectangleCorrectHeight = rectangleLeftTopPoint.GetPointY() - rectangleRightBottomPoint.GetPointY();
	WHEN("Testing GetWidth")
	{
		REQUIRE(rectangle.GetWidth() == rectangleCorrectWidth);
	}
	WHEN("Testing GetHeight")
	{

		REQUIRE(rectangle.GetHeight() == rectangleCorrectHeight);
	}

	WHEN("Testing GetPerimeter")
	{
		const double rectangleCorrectPerimeter = (rectangleCorrectWidth + rectangleCorrectHeight) * 2;
		REQUIRE(rectangle.GetPerimeter() == rectangleCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		const double rectangleCorrectArea = rectangleCorrectWidth * rectangleCorrectHeight;
		REQUIRE(rectangle.GetArea() == rectangleCorrectArea);
	}
}

SCENARIO("Testing CCircle")
{
	const CPoint circleCenterPoint = { 5, 5 };
	const double circleRadius = 5;

	const HexColor circleFillColor = 0xff00ff;
	const HexColor circleOutlineColor = 0x00ff00;

	const CCircle circle(circleCenterPoint, circleRadius, circleFillColor, circleOutlineColor);

	WHEN("Testing GetFillColor")
	{
		REQUIRE(circle.GetFillColor() == circleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(circle.GetOutlineColor() == circleOutlineColor);
	}
	WHEN("Testing GetPerimeter")
	{
		const double circleCorrectPerimeter = 2 * circleRadius * M_PI;
		REQUIRE(circle.GetPerimeter() == circleCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		const double circleCorrectArea = circleRadius * circleRadius * M_PI;
		REQUIRE(circle.GetArea() == circleCorrectArea);
	}
}

SCENARIO("Testing CLineSegment")
{
	const CPoint lineStartPoint = { 0, 0 };
	const CPoint lineEndPoint = { 5, 0 };

	const HexColor lineOutlineColor = 0x00ff00;

	const CLineSegment line(lineStartPoint, lineEndPoint, lineOutlineColor);

	WHEN("Testing GetStartPoint")
	{
		REQUIRE(line.GetStartPoint() == lineStartPoint);
	}
	WHEN("Testing GetEndPoint")
	{
		REQUIRE(line.GetEndPoint() == lineEndPoint);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(line.GetOutlineColor() == lineOutlineColor);
	}
	WHEN("Testing GetPerimeter")
	{
		const double lineCorrectPerimeter = CPoint::GetDistance(lineEndPoint, lineStartPoint);
		REQUIRE(line.GetPerimeter() == lineCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		const double lineCorrectArea = 0;
		REQUIRE(line.GetArea() == lineCorrectArea);
	}
}

SCENARIO("Testing ShapeController")
{
	WHEN("Creating Line using ShapeController")
	{
		THEN("Line has been successfully created")
		{
			std::istringstream inputStream("line 0 0 5 5 ff00ffff \nprintAllShapes");
			std::ostringstream outputStream;
			const ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Line has been created." << std::endl
								<< "LINE" << std::endl
								<< "Start Point: (0.00, 0.00)" << std::endl
								<< "End Point: (5.00, 5.00)" << std::endl
								<< "Outline Color: #ff00ffff" << std::endl
								<< "Area: 0.00" << std::endl
								<< "Perimiter: 7.07" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Triangle using ShapeController")
	{
		THEN("Triangle has been successfully created")
		{
			std::istringstream inputStream("triangle 0 0 5 5 2 2 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			const ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Triangle has been created." << std::endl
								<< "TRIANGLE" << std::endl
								<< "Vertex #1: (0.00, 0.00)" << std::endl
								<< "Vertex #2: (5.00, 5.00)" << std::endl
								<< "Vertex #3: (2.00, 2.00)" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 0.00" << std::endl
								<< "Perimiter: 14.14" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Rectangle using ShapeController")
	{
		THEN("Rectangle has been successfully created")
		{
			std::istringstream inputStream("rectangle 10 10 15 0 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			const ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Rectangle has been created." << std::endl
								<< "RECTANGLE" << std::endl
								<< "Left Top Point: (10.00, 10.00)" << std::endl
								<< "Right Bottom Point: (15.00, 0.00)" << std::endl
								<< "Width: 5.00" << std::endl
								<< "Height: 10.00" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 50.00" << std::endl
								<< "Perimiter: 30.00" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Circle using ShapeController")
	{
		THEN("Circle has been successfully created")
		{
			std::istringstream inputStream("circle 0 0 5 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			const ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Circle has been created." << std::endl
								<< "CIRCLE" << std::endl
								<< "Center: (0.00, 0.00)" << std::endl
								<< "Radius: 5.00" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 78.54" << std::endl
								<< "Perimiter: 31.42" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
}
