#ifndef _RAWCIRCLE_H_
#define _RAWCIRCLE_H_

#include "RawShape.h"
#include "../element/circle.h"
#include "../vector/vector2.h"

class RawCircle : public RawShape
{
private:
	Vec2 center;
	double radius;

public:
	RawCircle(const Vec2& center, double radius);
	Shape* preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) override;
};

#endif