#include "../../inc/parser/parser.h"
#include "../../inc/parser/parseElements.h"
#include "../../inc/vector/matrix3.h"

#include <fstream>
#include <iostream>

//Initialize Parser object as NULL
Parser* Parser::parser_ptr = 0;

//------------------------------------------------
//------------------- INTERNAL -------------------
//------------------------------------------------
static void parse_matrix3(std::fstream& f, Matrix3& m)
{
	double e[9];
	for(int i = 0; i < 9; i++) f>>e[i];
	m.set(e);
}

static void parse_rect(std::fstream& f, Rect& w)
{
	double x, y;
	Vec2 v;
	
	f>>x; f>>y; v.set(x, y);
	w.setLeftBottom( v );

	f>>x; f>>y; v.set(x, y);
	w.setRightTop( v );
}

static void parse_element(std::fstream& f, std::vector<RawElement>& rawVector)
{
	std::string aux;
	RawElement raw;

	//Parse shape
	std::string shape_type, shape_data;
	f>>shape_type; std::getline(f, shape_data);

	RawShape* shape = ParseElement::instance()->parseShapeByType(shape_type, shape_data);

	//Parse shape transformation
	std::string shape_transf;
	f>>aux; 						//TODO: Check for errors here

	Matrix3 trans_shape;
	parse_matrix3(f, trans_shape);

	//Parse paint
	std::string paint_type, paint_data;
	f>>paint_type; std::getline(f, paint_data);

	RawPaint* paint = ParseElement::instance()->parsePaintByType(paint_type, paint_data);

	//Parse paint transformation
	f>>aux; 						//TODO: Check for errors here

	Matrix3 trans_paint;
	parse_matrix3(f, trans_paint);

	//push final object
	raw.setShape(shape, trans_shape);
	raw.setPaint(paint, trans_paint);

	rawVector.push_back( raw );
}

static void parse_viewport(std::fstream& f, Vec2& v)
{
	int w, h;
	f>>w; f>>h;
	v.set( w, h );
}

//-----------------------------------------------------
//------------------- FROM PARSER.H -------------------
//-----------------------------------------------------
Parser::Parser()
{
	
}

int Parser::loadScene(std::string filepath, std::vector<RawElement>& raw, Rect& window, Vec2& viewport, Matrix3& scene_t)
{
	std::string buffer;
	std::fstream file;
	int nElem;

	file.open(filepath.c_str(), std::ios_base::in);

	if( !file.is_open() ) return -1;

	//window data
	file>>buffer;
	if( buffer.compare("WINDOW") ) return -1;
	parse_rect(file, window);

	//viewport data
	file>>buffer;
	if( buffer.compare("VIEWPORT") ) return -1;
	parse_viewport(file, viewport);

	//scene transformation
	file>>buffer;
	if( buffer.compare("TRANSFORM") ) return -1;
	parse_matrix3(file, scene_t);
	
	//starting reading elements
	file>>buffer;
	if( buffer.compare("ELEMENTCOUNT") ) return -1;
	file>>nElem;

	for(int i = 0; i < nElem; i++)
		parse_element(file, raw);

	file.close();

	return 0;
}
