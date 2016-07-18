#ifndef _RAW_TRIANGLE_H_
#define _RAW_TRIANGLE_H_

#include "RawShape.h"
#include "../vector/vector2.h"
#include "../element/triangle.h"

class RawTriangle : public RawShape
{
private:
	Vec2 p0_, p1_, p2_;

public:
	RawTriangle();
	RawTriangle(const Vec2& p0, const Vec2& p1, const Vec2& p2);
	
	//--------------------------
	//----- From RawShape ------
	//--------------------------
	Shape* preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) override;
};

#endif