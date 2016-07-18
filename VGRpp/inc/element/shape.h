#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "../vector/matrix3.h"

class Shape
{
protected:
	//TODO: Shape shouldn't modify internal copy of scenexf!!!
	//How to do this without creating a similar class with access-only
	//members?!
	Matrix3 scene_xf;

public:
	Matrix3 get_scenexf() const { return this->scene_xf; }
	
	virtual void set_scenexf(const Matrix3& scene_xf) { this->scene_xf = scene_xf; }
	virtual bool is_inside(double x, double y) = 0;
};

#endif