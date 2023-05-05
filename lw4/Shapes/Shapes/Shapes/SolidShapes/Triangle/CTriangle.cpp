#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, HexColor fillColor, HexColor outlineColor)
	: CSolidShape(fillColor, outlineColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}


double CTriangle::GetArea() const
{
	double halfPerimeter = GetPerimeter() / 2;
	double distanceVertex12 = CPoint::GetDistance(m_vertex1, m_vertex2);
	double distanceVertex13 = CPoint::GetDistance(m_vertex1, m_vertex3);
	double distanceVertex23 = CPoint::GetDistance(m_vertex2, m_vertex3);

	double triangleArea = sqrt(halfPerimeter * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12));
	return triangleArea;
}

double CTriangle::GetPerimeter() const
{
	double distanceVertex12 = CPoint::GetDistance(m_vertex1, m_vertex2);
	double distanceVertex13 = CPoint::GetDistance(m_vertex1, m_vertex3);
	double distanceVertex23 = CPoint::GetDistance(m_vertex2, m_vertex3);

	double trianglePerimeter = distanceVertex12 + distanceVertex13 + distanceVertex23;
	return trianglePerimeter;
}

std::string CTriangle::ToString() const
{
	std::ostringstream outputStream;
	outputStream << std::fixed << std::setprecision(2)
				 << "TRIANGLE" << std::endl
				 << "Vertex #1: (" << m_vertex1.GetPointX() << ", " << m_vertex1.GetPointY() << ")" << std::endl
				 << "Vertex #2: (" << m_vertex2.GetPointX() << ", " << m_vertex2.GetPointY() << ")" << std::endl
				 << "Vertex #3: (" << m_vertex3.GetPointX() << ", " << m_vertex3.GetPointY() << ")" << std::endl
				 << "Outline Color: #" << std::hex << GetOutlineColor() << std::endl
				 << "Fill Color: #" << std::hex << GetFillColor() << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimiter: " << GetPerimeter() << std::endl;
	return outputStream.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 }, GetFillColor());
	canvas.DrawLine(m_vertex1, m_vertex2, GetOutlineColor());
	canvas.DrawLine(m_vertex2, m_vertex3, GetOutlineColor());
	canvas.DrawLine(m_vertex1, m_vertex3, GetOutlineColor());
}
