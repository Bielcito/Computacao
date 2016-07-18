#ifndef _SOLID_H_
#define _SOLID_H_

#include "../color.h"
#include "../vector/matrix3.h"
#include "./paint.h"
using Color::ColorRGBA;
using Color::ColorChnl;

class Solid : public Paint
{
private:
	ColorRGBA _color;

public:
	Solid();
	Solid(ColorRGBA c);
	Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a);

	//-----------------------------
	//-------- From Paint ---------
	//-----------------------------
	ColorRGBA sample(double x, double y) override;
};

#endif