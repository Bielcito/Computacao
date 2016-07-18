#include "../../../inc/element/path/line.h"

//--------------------------------
//----------- Internal -----------
//--------------------------------
static void compute_implicit_line(const Vec2& p0, const Vec2& p1, double* coef)
{
	double a = p1.y() - p0.y();
	double b = p0.x() - p1.x();
	double c = -a*p0.x() - b*p0.y();
	int sign = (a > 0) ? +1 : -1;

	coef[0] = a*sign;
	coef[1] = b*sign;
	coef[2] = c*sign;
}

//-----------------------------------
//----------- From Line.h -----------
//-----------------------------------
void Line::setAABB()
{
	min.setX( p1.x() < p2.x() ? p1.x() : p2.x() );
	min.setY( p1.y() < p2.y() ? p1.y() : p2.y() );

	max.setX( p1.x() > p2.x() ? p1.x() : p2.x() );
	max.setY( p1.y() > p2.y() ? p1.y() : p2.y() );
}

inline void Line::setDY()
{
	int diff = p2.y() - p1.y();
	if(diff > 0)
		dy = +1;
	else if(diff < 0)
		dy = -1;
	else
		dy = 0;
}

Line::Line(const Vec2& p1, const Vec2& p2) 
{
	this->p1 = p1;
	this->p2 = p2;
	this->_p1 = p1;
	this->_p2 = p2;

	setAABB();
	setDY();
	compute_implicit_line(this->p1, this->p2, this->coef);
}

//--------------------------------------------
//------------ FROM PRIMITIVE.H --------------
//--------------------------------------------
std::string Line::prim2str()
{
	std::stringstream ss;
	ss<<"Line[("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<")]";
	return ss.str();
}

void Line::transform(const Matrix3& t) 
{
	this->p1 = t.apply( this->_p1.homogeneous() ).euclidean();
	this->p2 = t.apply( this->_p2.homogeneous() ).euclidean();
	
	setAABB();
	setDY();
	compute_implicit_line(this->p1, this->p2, this->coef);
}

int Line::to_the_left(const Vec2& p)
{
	if(min.y() <= p.y() && p.y() < max.y())
	{
		if(p.x() <= min.x()) return dy;
		if(p.x() > max.x()) return 0;

		return ( coef[0]*p.x() + coef[1]*p.y() + coef[2] <= 0 ) ? dy : 0;
	}
	return 0;
}