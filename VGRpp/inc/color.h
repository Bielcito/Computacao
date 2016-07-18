#ifndef _TYPES_H_
#define _TYPES_H_

#include "vector/numeric.h"
#include <vector>
#include <utility>

namespace Color
{
	//----------------------------------------
	//------------- Data types ---------------
	//----------------------------------------
	typedef unsigned char 	ColorChnl;
	typedef unsigned int	ColorRGBA;

	const ColorRGBA FULL_TRANSPARENT = 0x00000000;

	typedef struct {
		double R, G, B, A;
	} Color_v;

	//----------------------------------------------
	//------------- Color operations ---------------
	//----------------------------------------------
	ColorRGBA rgba_from_colorv(const Color_v& c);
	Color_v colorv_from_rgba(ColorRGBA c);
	ColorRGBA rgba_from_components(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a);
	
	double alpha_composite(double c_top, double a_top, double c_bottom, double a_bottom);
	Color_v color_over(const Color_v& top, const Color_v& bottom);
	ColorRGBA color_over(ColorRGBA top, ColorRGBA bottom);
	
	Color_v color_lerp(double t, const Color_v& c1, const Color_v& c2);
	
	double get_stop(double v, Color_v& s1, Color_v& s2, const std::vector<std::pair<double,Color_v> >& ramp);
};

#endif