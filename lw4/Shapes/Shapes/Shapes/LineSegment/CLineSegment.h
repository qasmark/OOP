#pragma once
#include "../../Point/CPoint.h"
#include "../IShape.h"
#include <iomanip>
#include <sstream>

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, HexColor outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	HexColor GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	HexColor m_outlineColor;
};
