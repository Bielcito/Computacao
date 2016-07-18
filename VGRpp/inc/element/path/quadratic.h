#ifndef _QUADRATIC_H_
#define _QUADRATIC_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>
#include <iostream>

//It is never enough to remind: all quadratics are MONOTONIC, as we
//monotonize them in the RawPrimitive preprocessing pass

class Quadratic : public Primitive
{
private:
	Vec2 p0, p1, p2;

	//Ascending or descending curve?
	int dy;

	//AABB (axis aligned bounding box)
	Vec2 min, max;

	//These Vec2 hold always the original values (crappy software engineering again)
	Vec2 _p0, _p1, _p2;

	void setAABB();
	void setDY();
	void recompute_param();

public:
	//----------------------------
	//------- Constructors -------
	//----------------------------
	Quadratic();
	Quadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2);

	//------------------------------
	//------- Access methods -------
	//------------------------------
	void set_p0(const Vec2& _p0);
	void set_p1(const Vec2& _p1);
	void set_p2(const Vec2& _p2);

	//--------------------------------
	//------- From Quadratic.h -------
	//--------------------------------
	std::string prim2str() override;
	void transform(const Matrix3& t) override;
	int to_the_left(const Vec2& p) override;
};

#endif