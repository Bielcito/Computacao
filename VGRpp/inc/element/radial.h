#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "paint.h"
#include "../spread.h"
#include "../vector/numeric.h"
#include <vector>
using Color::Color_v;
using Color::ColorRGBA;
using Spread::spread_func;


#include <iostream>

class Radial : public Paint
{
private:
	double center;
	spread_func spread;
	std::vector<std::pair<double,Color_v> > stops;
	Matrix3 canonical_grad;

public:
	Radial(spread_func spr, 
			double center, 
			const Matrix3& world2canonical, 
			const std::vector<std::pair<double, Color_v> >& stops);

	//-----------------------------
	//------- From paint.h --------
	//-----------------------------
	ColorRGBA sample(double x, double y) override;
};

#endif