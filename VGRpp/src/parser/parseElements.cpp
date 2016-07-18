#include "../../inc/parser/parseElements.h"

#include <iostream>
#include <sstream>
#include "../../inc/color.h"
#include "../../inc/vector/vector2.h"
#include "../../inc/vector/vector3.h"
#include "../../inc/RawElement/RawTriangle.h"
#include "../../inc/RawElement/RawCircle.h"
#include "../../inc/RawElement/RawSolid.h"
#include "../../inc/RawElement/RawLinear.h"
#include "../../inc/RawElement/RawRadial.h"
#include "../../inc/RawElement/RawTexture.h"
#include "../../inc/RawElement/path/RawPath.h"
#include "../../inc/RawElement/path/RawQuadratic.h"
#include "../../inc/RawElement/path/RawRQuadratic.h"

ParseElement* ParseElement::parseElement_ptr = NULL;

ParseElement::ParseElement()
{
	//Create association between names in .2d files and parsing functions for shapes and paints.
	//TODO: SPLIT THIS INTO TWO SEPARATE FUNCTIONS
	this->type2shape.insert( std::pair<std::string, shapeFunc>(TRIANGLE, &ParseElement::parseTriangle) );
	this->type2shape.insert( std::pair<std::string, shapeFunc>(CIRCLE, &ParseElement::parseCircle) );
	this->type2shape.insert( std::pair<std::string, shapeFunc>(PATH, &ParseElement::parsePath) );

	this->type2paint.insert( std::pair<std::string, paintFunc>(SOLID, &ParseElement::parseSolid) );
	this->type2paint.insert( std::pair<std::string, paintFunc>(LINEAR, &ParseElement::parseLinear) );
	this->type2paint.insert( std::pair<std::string, paintFunc>(RADIAL, &ParseElement::parseRadial) );
	this->type2paint.insert( std::pair<std::string, paintFunc>(TEXTURE, &ParseElement::parseTexture) );
}

RawShape* ParseElement::parseShapeByType(std::string type, std::string data)
{
	shapeFunc f = type2shape[type];
	return (this->*f)(data);
}

RawPaint* ParseElement::parsePaintByType(std::string type, std::string data)
{
	paintFunc f = type2paint[type];
	return (this->*f)(data);
}

//-------------------------------------------------------------
//--------------------- SHAPE PARSING -------------------------
//-------------------------------------------------------------
RawShape* ParseElement::parseCircle(std::string data)
{
	std::stringstream ss(data);

	Vec2 center; double radius;
	
	double x, y;
	ss>>x>>y>>radius; center.set(x,y);

	return new RawCircle(center, radius);
}

RawShape* ParseElement::parseTriangle(std::string data)
{
	std::stringstream ss(data);
	double x, y;

	Vec2 p0, p1, p2;
	ss>>x>>y; p0.set(x, y);
	ss>>x>>y; p1.set(x, y);
	ss>>x>>y; p2.set(x, y);

	return new RawTriangle(p0, p1, p2);
}

RawShape* ParseElement::parsePath(std::string data)
{
	std::stringstream ss(data);
	std::string buffer;
	Vec2 current;
	RawPath *out = new RawPath();
	Vec2 first(-1, -1);

	//Read until we find a closing element Z
	ss>>buffer;
	while( buffer.compare("Z") )
	{
		if(!buffer.compare("M"))
		{
			double x, y;
			ss>>x>>y;
			current.setX(x); current.setY(y);

			if(first.x() == -1) first = current;
		}
		else if(!buffer.compare("L"))
		{	
			double x, y;
			ss>>x>>y;
			Vec2 next = Vec2(x, y);

			out->push_primitive( new RawLine(current, next) );

			current = next;
		}
		else if(!buffer.compare("Q"))
		{
			Vec2 p0 = current;

			double p1x, p1y;
			double p2x, p2y;
			ss>>p1x>>p1y;
			ss>>p2x>>p2y;

			Vec2 p1 = Vec2(p1x, p1y);
			Vec2 p2 = Vec2(p2x, p2y);

			out->push_primitive( new RawQuadratic(p0, p1, p2) );

			current = p2;
		}
		else if(!buffer.compare("RQ"))
		{
			Vec2 p0 = current;

			double p1x, p1y, r;
			double p2x, p2y;
			ss>>p1x>>p1y>>r;
			ss>>p2x>>p2y;

			Vec3 p1 = Vec3(p1x, p1y, r);
			Vec2 p2 = Vec2(p2x, p2y);

			out->push_primitive( new RawRationalQuadratic(p0, p1, p2) );

			current = p2;
		}

		//Get next instruction
		ss>>buffer;
	}

	//Close contour
	out->push_primitive( new RawLine(current, first) );

	return out;
}

//-------------------------------------------------------------
//--------------------- PAINT PARSING -------------------------
//-------------------------------------------------------------
RawPaint* ParseElement::parseSolid(std::string data)
{
	std::stringstream ss(data);

	unsigned int R, G, B, A;
	ss>>R;
	ss>>G;
	ss>>B;
	ss>>A;

	return new RawSolid( (ColorChnl)R, (ColorChnl)G, (ColorChnl)B, (ColorChnl)A);
}

RawPaint* ParseElement::parseLinear(std::string data)
{
	std::stringstream ss(data);

	RawLinear *rl = new RawLinear();

	std::string spread;
	ss>>spread;
	rl->set_spread_type(spread);

	double p0x, p0y, p1x, p1y;
	ss>>p0x>>p0y;
	ss>>p1x>>p1y;
	rl->set_p0( Vec2(p0x, p0y) );
	rl->set_p1( Vec2(p1x, p1y) );

	while(!ss.eof())
	{
		double stop; int color[4];

		ss>>stop;
		ss>>color[0]>>color[1]>>color[2]>>color[3];

		rl->push_stop(stop, (Color_v){color[0]/255.0, color[1]/255.0, color[2]/255.0, color[3]/255.0});
	}

	return rl;
}

RawPaint* ParseElement::parseRadial(std::string data)
{
	std::stringstream ss(data);

	RawRadial *rr = new RawRadial();

	std::string spread;
	ss>>spread;
	rr->set_spread_type(spread);

	double p0x, p0y, p1x, p1y;
	ss>>p0x>>p0y>>p1x>>p1y;
	rr->set_center( Vec2(p0x, p0y) );
	rr->set_focus( Vec2(p1x, p1y) );

	double r;
	ss>>r;
	rr->set_radius(r);

	while(!ss.eof())
	{
		double stop; Color_v color;
		ss>>stop;
		ss>>color.R>>color.G>>color.B>>color.A;

		//TODO: create a method for this
		color.R /= 255.0;
		color.G /= 255.0;
		color.B /= 255.0;
		color.A /= 255.0;

		rr->push_stop(stop, color);
	}

	return rr;
}

RawPaint* ParseElement::parseTexture(std::string data)
{
	std::stringstream ss(data);

	RawTexture *rt = new RawTexture();

	std::string spread;
	ss>>spread;
	rt->set_spread_type(spread);

	std::string image_url;
	ss>>image_url;
	rt->set_image_url(image_url);

	return rt;
}