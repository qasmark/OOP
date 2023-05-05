#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, HexColor outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}


double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return CPoint::GetDistance(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString() const
{
	std::ostringstream outputStream;
	outputStream << std::fixed << std::setprecision(2)
				 << "LINE" << std::endl
				 << "Start Point: (" << m_startPoint.GetPointX() << ", " << m_startPoint.GetPointY() << ")" << std::endl
				 << "End Point: (" << m_endPoint.GetPointX() << ", " << m_endPoint.GetPointY() << ")" << std::endl
				 << "Outline Color: #" << std::hex << GetOutlineColor() << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimiter: " << GetPerimeter() << std::endl;
	return outputStream.str();
}

HexColor CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
