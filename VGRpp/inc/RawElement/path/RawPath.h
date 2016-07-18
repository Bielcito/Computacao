#ifndef _RAW_PATH_H_
#define _RAW_PATH_H_

#include "../RawShape.h"
#include "./RawPrimitive.h"
#include "./RawLine.h"
#include "../../element/path/path.h"

#include <iostream>
#include <vector>

class RawPath : public RawShape
{
private:
	std::vector<RawPrimitive*> primitives;

public:
	RawPath() { }

	//TODO: Destructor should destroy everything inside primitives

	void push_primitive(RawPrimitive* prim);
	Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) override;
};

#endif