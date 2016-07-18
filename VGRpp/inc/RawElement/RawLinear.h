#ifndef _RAW_LINEAR_H_
#define _RAW_LINEAR_H_

#include "RawPaint.h"
#include "../element/linear.h"
#include "../spread.h"
#include "../vector/vector2.h"
#include "../color.h"
#include <vector>
#include <string>
#include <utility>
using Color::Color_v;
using Color::ColorRGBA;
using Spread::spread_func;

#include <iostream>
using std::cout;
using std::endl;

class RawLinear : public RawPaint
{
private:
	std::vector< std::pair<double,Color_v> > stops;
	
	Vec2 p0, p1;

	std::string spread;

public:
	//------------------------
	//----- Access stuff -----
	//------------------------
	void set_spread_type(const std::string& spread);
	void set_p0(const Vec2& p);
	void set_p1(const Vec2& p);
	void push_stop(double s, const Color_v& c);

	//----- From RawPaint.h -----
	Paint* preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf) override;
};

#endif