#ifndef _RATIONAL_QUADRATIC_H_
#define _RATIONAL_QUADRATIC_H_

#include "primitive.h"
#include "../../vector/vector2.h"
#include "../../vector/vector3.h"
#include "../../vector/numeric.h"
#include <sstream>

#include <iostream>
using std::cout;
using std::endl;

//Remember that an RQuadratic is ALWAYS monotonic,
//as we cut them while processing the raw rational quadratic
//Also, remember _p1 is already projected! i.e., is in form (x1w1, y1w1, w1)
class RQuadratic : public Primitive
{
private:
	Vec2 p0, p2;
	Vec3 p1;

	//these points won't change
	Vec2 _p0, _p2;
	Vec3 _p1;

	//ascending or descending curve
	double dy;

	//Axis Aligned Bounding Box
	Vec2 min, max;

	void setAABB();
	void recompute_param();

public:
	RQuadratic(const Vec2& p0, const Vec3& p1, const Vec2& p2);

	void set_p0(const Vec2& p);
	void set_p1(const Vec3& p);
	void set_p2(const Vec2& p);

	//-----------------------------------------
	//---------- FROM PRIMITIVE.h -------------
	//-----------------------------------------
	std::string prim2str() override;
	void transform(const Matrix3& t) override;
	int to_the_left(const Vec2& p) override;
};

#endif