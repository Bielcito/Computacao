#include "../../inc/vector/vector3.h"
#include "../../inc/vector/vector2.h"

Vec3::Vec3()
{
	_x = _y = _w = 0.0;
}

Vec3::Vec3(double x, double y, double w)
{
	this->_x = x;
	this->_y = y;
	this->_w = w;
}

Vec2 Vec3::euclidean()
{
	return Vec2(_x/_w, _y/_w);
}

double Vec3::dot(const Vec3& rhs) const
{
	return _x * rhs.x() + _y * rhs.y() + _w * rhs.w();
}