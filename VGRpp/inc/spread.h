#ifndef _SPREAD_FUNC_H_
#define _SPREAD_FUNC_H_

#include <string>

namespace Spread
{
	//All spread functions have this signature
	typedef double (*spread_func)(double);

	double spread_pad(double v);

	//This is kind of C-style Factory pattern
	spread_func spread_func_from_str(const std::string& spread);
};

#endif