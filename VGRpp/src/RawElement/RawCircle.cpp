#include "../../inc/RawElement/RawCircle.h"

RawCircle::RawCircle(const Vec2& center, double radius)
{
	this->center = center;
	this->radius = radius;
}

Shape* RawCircle::preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) 
{
	Circle *out = new Circle(this->center, this->radius);
	out->set_modelxf(model_xf);
	out->set_scenexf(scene_xf);	
	return out;
}