#pragma once
#include "../IShape.h"

class ISolidShape : public IShape
{
public:
	virtual HexColor GetFillColor() const = 0;
};