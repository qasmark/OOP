#pragma once
#include <iostream>

class CPoint
{
public:
	CPoint(double x = 0, double y = 0);
	double GetPointX() const;
	double GetPointY() const;

	static double GetDistance(const CPoint& point1, const CPoint& point2);

	bool operator==(const CPoint& otherPoint) const;
	friend std::istream& operator>>(std::istream& inputStream, CPoint& point);
private:
	double m_x;
	double m_y;
};
