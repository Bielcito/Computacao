#include "../../inc/element/solid.h"

Solid::Solid() 
{ 
	this->_color = 0; 
}

Solid::Solid(ColorRGBA c) 
{
	this->_color = c;
}

Solid::Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a) 
{
	this->_color = Color::rgba_from_components(r, g, b, a);
}

//-----------------------------
//-------- From Paint ---------
//-----------------------------
ColorRGBA Solid::sample(double x, double y)
{
	return _color;
}