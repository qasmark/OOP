#pragma once
#include "ICanvas.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);

	void DrawLine(const CPoint& startPoint, const CPoint& endPoint, HexColor lineColor) override;
	void FillPolygon(const std::vector<CPoint>& points, HexColor fillColor) override;
	void DrawCircle(const CPoint& centerPoint, double radius, HexColor lineColor) override;
	void FillCircle(const CPoint& centerPoint, double radius, HexColor fillColor) override;

	sf::RenderWindow& GetRenderedWindow();

private:
	sf::RenderWindow& m_renderWindow;
};
