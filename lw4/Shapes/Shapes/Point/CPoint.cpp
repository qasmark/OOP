#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetPointX() const
{
	return m_x;
}

double CPoint::GetPointY() const
{
	return m_y;
}


double CPoint::GetDistance(const CPoint& point1, const CPoint& point2)
{
	return sqrt(pow((point2.m_x - point1.m_x), 2) + pow((point2.m_y - point1.m_y), 2));
}

bool CPoint::operator==(const CPoint& otherPoint) const
{
	return (m_x == otherPoint.m_x && m_y == otherPoint.m_y);
}

std::istream& operator>>(std::istream& inputStream, CPoint& point)
{
	inputStream >> point.m_x >> point.m_y;
	return inputStream;
}
