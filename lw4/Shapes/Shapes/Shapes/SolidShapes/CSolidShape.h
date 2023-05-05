#pragma once

#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(HexColor fillColor, HexColor outlineColor);
	HexColor GetFillColor() const override;
	HexColor GetOutlineColor() const override;

private:
	HexColor m_fillColor;
	HexColor m_outlineColor;
};
