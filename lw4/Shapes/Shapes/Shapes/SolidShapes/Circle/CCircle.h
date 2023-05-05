#pragma once
#include "../../../Point/CPoint.h"
#include "../CSolidShape.h"
#include <iomanip>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& centerPoint, double radius, HexColor fillColor, HexColor outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_centerPoint;
	double m_radius;

};
