#include "../../inc/element/radial.h"

Radial::Radial(spread_func spr, double center, const Matrix3& world2canonical, const std::vector<std::pair<double, Color_v> >& stops)
{
	//capture STOPS with move semantics
	this->stops = std::move(stops);

	this->spread = spr;
	this->center = center;
	this->canonical_grad = world2canonical;
}

//-----------------------------
//------- From paint.h --------
//-----------------------------
ColorRGBA Radial::sample(double x, double y)
{
	// A ideia é a mesma: jogue o ponto (x,y) para o espaço
	// do gradiente canônico e calcule a interseção entre o raio
	// que vai da origem até (x,y). O seu parâmetro para interpolação
	// vai ser a razão do tamanho do vetor da origem até à interseção
	// e do tamanho do vetor (x,y). O resto é igual ao gradiente linear:
	// aplique a função spr_func, procure o valor na rampa, interpole as
	// cores, etc;
	Color_v out = {1.0, 1.0, 1.0, 1.0};

	return Color::rgba_from_colorv(out);
}