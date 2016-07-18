#include "../../inc/RawElement/RawTriangle.h"
#include "../../inc/element/triangle.h"

RawTriangle::RawTriangle() { }

RawTriangle::RawTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->p0_ = p0;
	this->p1_ = p1;
	this->p2_ = p2;
}

Shape* RawTriangle::preprocess(const Matrix3& model_xf, const Matrix3& scene_xf)
{
	Triangle* t = new Triangle(p0_, p1_, p2_);
	t->set_modelxf(model_xf);
	t->set_scenexf(scene_xf);
	return t;
}