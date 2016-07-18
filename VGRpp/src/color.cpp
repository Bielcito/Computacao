#include "../inc/color.h"

using Color::ColorRGBA;
using Color::Color_v;

ColorRGBA Color::rgba_from_colorv(const Color_v& c)
{
	ColorRGBA _color = 0;
	_color |= ( (ColorRGBA)(c.A*255) << 24 );
	_color |= ( (ColorRGBA)(c.R*255) << 16 );
	_color |= ( (ColorRGBA)(c.G*255) << 8 );
	_color |= (ColorRGBA)(c.B*255);

	return _color;
}

Color_v Color::colorv_from_rgba(ColorRGBA c)
{
	Color_v out;

	out.A = ((c & 0xFF000000) >> 24) / 255.0;
	out.R = ((c & 0x00FF0000) >> 16) / 255.0;
	out.G = ((c & 0x0000FF00) >> 8) / 255.0;
	out.B = (c & 0x000000FF) / 255.0;

	return out;
}

ColorRGBA Color::rgba_from_components(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a)
{
	ColorRGBA _color = 0;
	_color |= ( (ColorRGBA)a << 24 );
	_color |= ( (ColorRGBA)r << 16 );
	_color |= ( (ColorRGBA)g << 8 );
	_color |= (ColorRGBA)b;

	return _color;
}

double Color::alpha_composite(double c_top, double a_top, double c_bottom, double a_bottom)
{
	//Assumes non premultiplied values. Change this for performance!
	double num, den;
	num = c_top*a_top + c_bottom*a_bottom*(1.0 - a_top);
	den = a_top + a_bottom*(1.0 - a_top);
	return num/den;
}

Color_v Color::color_over(const Color_v& top, const Color_v& bottom)
{
	Color_v out;
	out.R = alpha_composite(top.R, top.A, bottom.R, bottom.A);
	out.G = alpha_composite(top.G, top.A, bottom.G, bottom.A);
	out.B = alpha_composite(top.B, top.A, bottom.B, bottom.A);
	out.A = top.A + bottom.A*(1 - top.A);

	return out;
}

ColorRGBA Color::color_over(ColorRGBA top, ColorRGBA bottom)
{
	return rgba_from_colorv( color_over( colorv_from_rgba(top), colorv_from_rgba(bottom) ) );
}

Color_v Color::color_lerp(double t, const Color_v& c1, const Color_v& c2)
{
	Color_v out;
	out.R = Numeric::lerp1(t, c1.R, c2.R);
	out.G = Numeric::lerp1(t, c1.G, c2.G);
	out.B = Numeric::lerp1(t, c1.B, c2.B);
	out.A = Numeric::lerp1(t, c1.A, c2.A);

	return out;
}

double Color::get_stop(double v, Color_v& s1, Color_v& s2, const std::vector<std::pair<double,Color_v> >& ramp)
{
	std::pair<double,Color_v> cur, last;
	int count = 1;
	last = ramp[count-1], cur = ramp[count];

	//TODO: This won't work if v is outside interval [0,1]!
	//Do error checking after
	while( cur.first < v )
	{
		last = cur;
		cur = ramp[++count];
	}

	s1 = last.second; s2 = cur.second;

	return v - last.first;
}