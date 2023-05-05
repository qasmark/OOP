#include "CRectangle.h"


CRectangle::CRectangle(const CPoint& leftTopPoint, const CPoint& rightBottomPoint, HexColor fillColor, HexColor outlineColor)
	: CSolidShape(fillColor, outlineColor)
	,
	m_leftTopPoint(leftTopPoint)
	, m_rightBottomPoint(rightBottomPoint)
{
}


double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return (GetHeight() + GetWidth()) * 2;
}

std::string CRectangle::ToString() const
{
	std::ostringstream outputStream;
	outputStream << std::fixed << std::setprecision(2)
				 << "RECTANGLE" << std::endl
				 << "Left Top Point: (" << m_leftTopPoint.GetPointX() << ", " << m_leftTopPoint.GetPointY() << ")" << std::endl
				 << "Right Bottom Point: (" << m_rightBottomPoint.GetPointX() << ", " << m_rightBottomPoint.GetPointY() << ")" << std::endl
				 << "Width: " << GetWidth() << std::endl
				 << "Height: " << GetHeight() << std::endl
				 << "Outline Color: #" << std::hex << GetOutlineColor() << std::endl
				 << "Fill Color: #" << std::hex << GetFillColor() << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimiter: " << GetPerimeter() << std::endl;
	return outputStream.str();
}


void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint rightTopPoint = { m_rightBottomPoint.GetPointX(), m_leftTopPoint.GetPointY() };
	CPoint leftBottomPoint = { m_leftTopPoint.GetPointX(), m_rightBottomPoint.GetPointY() };

	canvas.FillPolygon({ m_leftTopPoint, rightTopPoint, m_rightBottomPoint, leftBottomPoint }, GetFillColor());
	canvas.DrawLine(m_leftTopPoint, rightTopPoint, GetOutlineColor());
	canvas.DrawLine(rightTopPoint, m_rightBottomPoint, GetOutlineColor());
	canvas.DrawLine(m_rightBottomPoint, leftBottomPoint, GetOutlineColor());
	canvas.DrawLine(leftBottomPoint, m_leftTopPoint, GetOutlineColor());
}


double CRectangle::GetWidth() const
{
	return abs(m_rightBottomPoint.GetPointX() - m_leftTopPoint.GetPointX());
}

double CRectangle::GetHeight() const
{
	return abs(m_leftTopPoint.GetPointY() - m_rightBottomPoint.GetPointY());
}
