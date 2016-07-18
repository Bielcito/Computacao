#ifndef _LINE_H_
#define _LINE_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>

class Line : public Primitive
{
private:
	//These points can be transformed or not
	Vec2 p1, p2;

	//These points hold always the same value
	//(I know, crappy software engineering)
	Vec2 _p1, _p2;

	//AABB (axis aligned bounding box)
	Vec2 min, max;
	
	//Orientation and implicit representation of the line
	int dy; double coef[3];

	//set line orientation and axis-aligned bounding box
	void setAABB();
	void setDY();

public:
	Line() {}
	Line(const Vec2& p1, const Vec2& p2);

	//--------------------------------------------
	//------------ FROM PRIMITIVE.H --------------
	//--------------------------------------------
	std::string prim2str() override;
	void transform(const Matrix3& t) override;
	int to_the_left(const Vec2& p) override;
};

#endif