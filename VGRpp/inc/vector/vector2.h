#ifndef _VEC_2D_
#define _VEC_2D_

#include <string>
#include <sstream>

class Vec3;

class Vec2
{
private:
	double _x, _y;

public:

	//-------- Ctors ---------
	Vec2();
	Vec2(double x, double y);

	//-------- Access/modif --------
	double x() const { return this->_x; }
	double y() const { return this->_y; }
	void setX(double x) { this->_x = x; }
	void setY(double y) { this->_y = y; }
	void set(double x, double y) { this->_x = x; this->_y = y; }

	//This simply copies (x,y) attributes, no reference involved!!!
	void operator=(const Vec2& rhs);

	//-------- Operations --------
	Vec2 add(const Vec2& lhs) const;
	Vec2 scale(double s) const;
	double dot(const Vec2& lhs) const;
	Vec2 sub(const Vec2& lhs) const;
	double norm() const;
	double distTo(const Vec2& lhs) const;
	Vec2 unit() const;
	double angle(const Vec2& lhs) const;
	Vec2 prod(const Vec2& rhs) const; //Element-wise product
	Vec3 homogeneous() const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator-() const;
	Vec2 operator*(double s) const;
	Vec2 operator+(const Vec2& rhs) const;

	//-------- debugging ops --------
	std::string to_str() 
	{
		std::stringstream ss;
		ss<<"("<<_x<<", "<<_y<<")"; 
		return ss.str(); 
	}

	//-------- other stuff -------
	static Vec2 zero() { return Vec2(0.0, 0.0); }

};

#endif