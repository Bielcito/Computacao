#ifndef _RAWSHAPE_H_
#define _RAWSHAPE_H_

#include "../element/shape.h"
#include "../vector/matrix3.h"

class RawShape
{
public:
	virtual Shape* preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) = 0;
};

#endif