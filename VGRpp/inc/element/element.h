#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "../color.h"
#include "shape.h"
#include "paint.h"
#include "../vector/matrix3.h"
using Color::ColorRGBA;

#include <iostream>

class Element
{
private:
	Shape* _shape;
	Paint* _paint;

public:
	//---------------------------------
	//---------- CTORS/DTORS ----------
	//---------------------------------
	Element();
	Element(Shape* s, Paint* p);
	~Element();

	//------------------------------------
	//---------- ACCESS METHODS ----------
	//------------------------------------
	Shape* shape();
	Paint* paint();

	//----------------------------
	//---------- SAMPLE ----------
	//----------------------------
	void sample(double x, double y, ColorRGBA& out);
};

#endif