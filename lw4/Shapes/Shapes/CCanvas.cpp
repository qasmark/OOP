#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_renderWindow(window)
{
}

void CCanvas::DrawLine(const CPoint& startPoint, const CPoint& endPoint, HexColor lineColor)
{
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f((float)startPoint.GetPointX(), (float)startPoint.GetPointY())),
		sf::Vertex(sf::Vector2f((float)endPoint.GetPointX(), (float)endPoint.GetPointY()))
	};
	line[0].color = sf::Color(lineColor);
	line[1].color = sf::Color(lineColor);

	m_renderWindow.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, HexColor fillColor)
{
	sf::ConvexShape convex;
	convex.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		convex.setPoint(i, sf::Vector2f((float)points[i].GetPointX(), (float)points[i].GetPointY()));
	}
	sf::Color color(fillColor);
	convex.setFillColor(color);

	m_renderWindow.draw(convex);
}

void CCanvas::DrawCircle(const CPoint& centerPoint, double radius, HexColor lineColor)
{
	sf::CircleShape circle((float)radius);
	circle.setPosition((float)centerPoint.GetPointX() - (float)radius, (float)centerPoint.GetPointY() - (float)radius);

	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color(lineColor));

	m_renderWindow.draw(circle);
}

void CCanvas::FillCircle(const CPoint& centerPoint, double radius, HexColor fillColor)
{
	sf::CircleShape circle;
	circle.setRadius((float)radius);
	circle.setPosition((float)centerPoint.GetPointX() - (float)radius, (float)centerPoint.GetPointY() - (float)radius);

	circle.setFillColor(sf::Color(fillColor));

	m_renderWindow.draw(circle);
}

sf::RenderWindow& CCanvas::GetRenderedWindow()
{
	return m_renderWindow;
}
