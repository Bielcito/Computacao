#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "../vector/vector2.h"
#include "../vector/matrix3.h"
#include "../element/shape.h"
#include <cmath>

#include <iostream>

class Circle: public Shape
{
private:
	Vec2 center;
	double radius;
	Matrix3 model_xf;

	//Matrix describing this circle/ellipsis
	Matrix3 conic;

	//Sends point in viewport space to unit circle
	Matrix3 to_unit;

public:
	Circle(const Vec2& center, double radius);

	void set_modelxf(const Matrix3& xf);
	void update_conic();

	//-------------------------------
	//-------- From Circle.h --------
	//-------------------------------
	void set_scenexf(const Matrix3& xf) override;
	bool is_inside(double x, double y) override;
};

#endif