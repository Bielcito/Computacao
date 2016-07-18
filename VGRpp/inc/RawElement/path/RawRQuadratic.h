#ifndef _RAW_R_QUADRATIC_H_
#define _RAW_R_QUADRATIC_H_

#include "../../vector/vector2.h"
#include "../../vector/vector3.h"
#include "../../vector/numeric.h"
#include "RawPrimitive.h"
#include "../../element/path/rquadratic.h"
#include <sstream>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

class RawRationalQuadratic : public RawPrimitive
{
private:
	Vec2 p0, p2;
	Vec3 p1;

	void compute_maxima(double x0, double x1, double w, double x2, double& r1, double& r2);
	void cut_at(double a, double b, RQuadratic& out);

public:
	RawRationalQuadratic(const Vec2& p0, const Vec3& p1, const Vec2& p2);

	//---------------------------------------
	//--------- From RawPrimitive.h ---------
	//---------------------------------------
	std::string prim2str() override;
	void preprocess(std::vector<Primitive*>& holder) override;
	void transform(const Matrix3& t) override;
};

#endif