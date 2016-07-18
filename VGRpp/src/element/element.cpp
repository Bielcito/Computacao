#include "../../inc/element/element.h"

Element::Element() 
{
	_shape = 0;
	_paint = 0;
}

Element::Element(Shape* s, Paint* p) 
{
	this->_shape = s;
	this->_paint = p;
}

Element::~Element() 
{
	delete _shape; _shape = NULL;
	delete _paint; _paint = NULL;
}

//------------------------------------
//---------- ACCESS METHODS ----------
//------------------------------------
Shape* Element::shape() { return _shape; }
Paint* Element::paint() { return _paint; }

//----------------------------
//---------- SAMPLE ----------
//----------------------------
void Element::sample(double x, double y, ColorRGBA& out)
{
	if( _shape->is_inside(x,y) ) 
		out = _paint->sample(x, y);
	else out = Color::FULL_TRANSPARENT;
}