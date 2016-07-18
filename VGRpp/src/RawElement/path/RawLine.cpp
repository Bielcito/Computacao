#include "../../../inc/RawElement/path/RawLine.h"

RawLine::RawLine(Vec2 p1, Vec2 p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

std::string RawLine::prim2str() 
{
	std::stringstream out;

	out<<"RawLine["<<p1.x()<<", "<<p1.y()<<" -> "<<p2.x()<<", "<<p2.y()<<"]";

	return out.str();
}

void RawLine::preprocess(std::vector<Primitive*>& holder) 
{ 
	holder.push_back( new Line(p1, p2) ); 
}

void RawLine::transform(const Matrix3& t)
{
	p1 = t.apply( p1.homogeneous() ).euclidean();
	p2 = t.apply( p2.homogeneous() ).euclidean();
}