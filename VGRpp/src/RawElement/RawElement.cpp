#include "../../inc/RawElement/RawElement.h"

RawElement::RawElement()
{
	shape = NULL;
	paint = NULL;
}

RawElement::~RawElement()
{
	if(!shape) delete shape;
	if(!paint) delete paint;
}

void RawElement::setShape(RawShape* s, Matrix3& t)
{
	this->shape = s;
	this->shapexf = t;
}

void RawElement::setPaint(RawPaint* p, Matrix3& t)
{
	this->paint = p;
	this->paintxf = t;
}

void RawElement::preprocess(std::vector<Element*>& pool, const Matrix3& scene_t)
{
	Element* e = new Element( shape->preprocess(shapexf, scene_t), paint->preprocess(paintxf, scene_t) );
	pool.push_back(e);
}