#ifndef _PATH_H_
#define _PATH_H_

#include "../../vector/matrix3.h"
#include "../shape.h"
#include "./primitive.h"
#include "./line.h"

#include <vector>
#include <iostream>

class Path : public Shape
{
private:
	std::vector<Primitive*> primitives;
	Matrix3 model_xf;

	//Applies transformation to all primitives in path
	void transform_primitives();

public:

	//----------------------------------------
	//------------ ACCESS METHODS ------------
	//----------------------------------------
	void push_primitive(Primitive* p);
	void set_modelxf(const Matrix3& model_xf);

	//--------------------------------------
	//------------ FROM SHAPE.H ------------
	//--------------------------------------
	void set_scenexf(const Matrix3& scene_xf) override;
	bool is_inside(double x, double y) override;
};

#endif