#ifndef _RAW_RADIAL_H_
#define _RAW_RADIAL_H_

#include "RawPaint.h"
#include "../element/radial.h"
#include "../spread.h"

using Spread::spread_func;

#include <iostream>
using std::cout;
using std::endl;

class RawRadial : public RawPaint
{
private:
	std::string spr;
	Vec2 center, focus;
	double radius;
	std::vector<std::pair<double,Color_v> > stops;

public:

	//------------------------------------
	//---------- Access methods ----------
	//------------------------------------
	void set_spread_type(const std::string& spread);
	void set_center(const Vec2& p);
	void set_focus(const Vec2& p);
	void set_radius(double r);
	void push_stop(double s, const Color_v& color);

	//-------------------------------------
	//---------- From RawPaint.h ----------
	//-------------------------------------
	Paint* preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf) override;
};

#endif