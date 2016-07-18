#ifndef _PAINT_H_
#define _PAINT_H_

#include "../color.h"
#include "../vector/matrix3.h"
using Color::ColorRGBA;

class Paint
{
private:
	//Internal copy of scene transformation. This should not
	//be modified by Paint (or derived) class!
	Matrix3 scene_xf;

public:
	void set_scenexf(const Matrix3& scene_xf) { this->scene_xf = scene_xf; }
	Matrix3 get_scenexf() const { return this->scene_xf; }

	virtual ColorRGBA sample(double x, double y) = 0;
};

#endif