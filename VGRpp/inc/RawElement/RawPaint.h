#ifndef _RAWPAINT_H_
#define _RAWPAINT_H_

#include "../element/paint.h"
#include "../vector/matrix3.h"

class RawPaint
{
public:
	virtual Paint* preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) = 0;
};

#endif