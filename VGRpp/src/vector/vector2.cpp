#include <math.h>
#include "../../inc/vector/vector2.h"
#include "../../inc/vector/vector3.h"

//---------------------------------
//------------- CTORS -------------
//---------------------------------
Vec2::Vec2(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

Vec2::Vec2() : Vec2(0.0, 0.0) { }

//-----------------------------------------
//------------- ACCESS/MODIFY -------------
//-----------------------------------------
void Vec2::operator=(const Vec2& rhs)
{
	this->_x = rhs.x();
	this->_y = rhs.y();
}

//--------------------------------------
//------------- OPERATIONS -------------
//--------------------------------------
Vec2 Vec2::add(const Vec2& lhs) const {
	return Vec2(this->_x + lhs.x(), this->_y + lhs.y());
}

Vec2 Vec2::scale(double s) const {
	return Vec2(s*this->_x, s*this->_y);
}

double Vec2::dot(const Vec2& lhs) const {
	return this->_x * lhs.x() + this->_y * lhs.y();
}

Vec2 Vec2::sub(const Vec2& lhs) const {
	return add( lhs.scale(-1) );
}

double Vec2::norm() const {
	return sqrt( this->_x*this->_x + this->_y*this->_y );
}

double Vec2::distTo(const Vec2& lhs) const {
	return sub(lhs).norm();
}

Vec2 Vec2::unit() const {
	//(!!!) Watch out for divisions!
	return scale( 1 / norm() ) ;
}

double Vec2::angle(const Vec2& lhs) const {
	//(!!!) Watch out for divisions!
	return acos( dot(lhs) / norm() * lhs.norm() );
}

Vec2 Vec2::prod(const Vec2& rhs) const {
	return Vec2( _x * rhs.x(), _y * rhs.y() );
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return this->sub(rhs);
}

Vec2 Vec2::operator-() const {
	return this->scale(-1.0);
}

Vec2 Vec2::operator*(double s) const {
	return this->scale(s);
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return this->add(rhs);
}

Vec3 Vec2::homogeneous() const {
	return Vec3(_x, _y, 1.0);
}