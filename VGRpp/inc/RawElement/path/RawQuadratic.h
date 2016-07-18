#ifndef _RAW_QUADRATIC_
#define _RAW_QUADRATIC_

#include <string>
#include <sstream>
#include <vector>
#include "../../vector/vector2.h"
#include "../../vector/numeric.h"
#include "../../element/path/quadratic.h"
#include "./RawPrimitive.h"

#include <iostream>

class RawQuadratic : public RawPrimitive
{
private:
	Vec2 p0, p1, p2;
	 
	void cut_at(double t0, double t1, Quadratic& out);

public:
	RawQuadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2);

	//--------------------------------------
	//-------- From RawPrimitive.h ---------
	//--------------------------------------
	std::string prim2str() override;
	void transform(const Matrix3& t) override;
	void preprocess(std::vector<Primitive*>& holder) override;
};

#endif