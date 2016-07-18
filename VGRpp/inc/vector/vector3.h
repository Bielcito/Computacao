#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <sstream>
#include <string>

class Vec2;

class Vec3
{
private:
	double _x, _y, _w;
public:
	Vec3();
	Vec3(double x, double y, double w);

	//--------------------------
	//-------- Access ----------
	//--------------------------
	void setX(double x) { this->_x = x; }
	void setY(double y) { this->_y = y; }
	void setW(double w) { this->_w = w; }

	double x() const { return this->_x; }
	double y() const { return this->_y; }
	double w() const { return this->_w; }

	//-------------------------------
	//-------- debugging ops --------
	//-------------------------------
	std::string to_str() 
	{
		std::stringstream ss;
		ss<<"("<<_x<<", "<<_y<<", "<<_w<<")"; 
		return ss.str(); 
	}

	//--------------------------
	//------- Operations -------
	//--------------------------
	Vec2 euclidean();
	double dot(const Vec3& rhs) const;
};

#endif