#pragma once
#include "CPoint.h"
#include <vector>

using HexColor = uint32_t;

class ICanvas
{
public:
	// ������� �������� HexColor ��������������
	virtual void DrawLine(const CPoint& startPoint, const CPoint& endPoint, HexColor lineColor) = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, HexColor fillColor) = 0;
	virtual void DrawCircle(const CPoint& centerPoint, double radius, HexColor lineColor) = 0;
	virtual void FillCircle(const CPoint& centerPoint, double radius, HexColor fillColor) = 0;

	virtual ~ICanvas() = default;
};