#include "../inc/spread.h"

using Spread::spread_func;

double Spread::spread_pad(double v)
{
	if(v > 1.0) return 1;
	else if(v < 0) return 0;
	else return v;
}

spread_func Spread::spread_func_from_str(const std::string& spread)
{
	if(!spread.compare("PAD"))
		return spread_pad;
}