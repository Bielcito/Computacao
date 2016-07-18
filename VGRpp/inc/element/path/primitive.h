#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <string>
#include "../../vector/matrix3.h"

class Primitive
{
private:
public:
	virtual std::string prim2str() = 0;
	virtual void transform(const Matrix3& t) = 0;

	//Returns ZERO if the ray casted in the x direction
	//does not intersects with the primitive; if there is 
	//such an intersection, returns -1 or +1 depending on
	//the direction the primitive is going (down or up) 
	virtual int to_the_left(const Vec2& p) = 0;
};

#endif