#pragma once
#include "../../../Point/CPoint.h"
#include "../CSolidShape.h"
#include <sstream>
#include <iomanip>

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint& leftTopPoint, const CPoint& rightBottomPoint, HexColor fillColor, HexColor outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas& canvas) const override;

	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTopPoint;
	CPoint m_rightBottomPoint;
};
