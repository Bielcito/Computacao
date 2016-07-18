#ifndef _PARSE_ELEMENTS_
#define _PARSE_ELEMENTS_

#include <string>
#include <map>
#include "../RawElement/RawElement.h"

class ParseElement;
typedef RawShape* (ParseElement::*shapeFunc)(std::string);
typedef RawPaint* (ParseElement::*paintFunc)(std::string);

//----------------------------------
//----------- SHAPE TAGS -----------
//----------------------------------
//These are the tags as they appear in .2d files
const std::string TRIANGLE("TRIANGLE");
const std::string CIRCLE("CIRCLE");
const std::string PATH("PATH");

//----------------------------------
//----------- PAINT TAGS -----------
//----------------------------------
//These are the tags as they appear in .2d files
const std::string SOLID("SOLID");
const std::string LINEAR("LINEAR");
const std::string RADIAL("RADIAL");
const std::string TEXTURE("TEXTURE");

class ParseElement
{
private:

	static ParseElement* parseElement_ptr;
	ParseElement();

	std::map<std::string, shapeFunc> type2shape;
	std::map<std::string, paintFunc> type2paint;

	//-------------------------------------
	//----------- PARSE SHAPES ------------
	//-------------------------------------
	//All these functions, of type shapeFunc, 
	//return a pointer to the parent class whose 
	//dynamic type is of the desired shape
	RawShape* parseTriangle(std::string);
	RawShape* parseCircle(std::string);
	RawShape* parsePath(std::string);

	//-------------------------------------
	//----------- PARSE PAINTS ------------
	//-------------------------------------
	//All these functions, of type paintFunc, 
	//return a pointer to the parent class whose 
	//dynamic type is of the desired paint
	//TODO: pass strings by const reference!
	RawPaint* parseSolid(std::string);
	RawPaint* parseLinear(std::string);
	RawPaint* parseRadial(std::string);
	RawPaint* parseTexture(std::string);

public:

	static ParseElement* instance() {
		if(!ParseElement::parseElement_ptr)
			ParseElement::parseElement_ptr = new ParseElement();
		return ParseElement::parseElement_ptr;
	}

	RawShape* parseShapeByType(std::string type, std::string data);
	RawPaint* parsePaintByType(std::string type, std::string data);
};

#endif