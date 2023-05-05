#include "CSolidShape.h"

CSolidShape::CSolidShape(HexColor fillColor, HexColor outlineColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

HexColor CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

HexColor CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}
