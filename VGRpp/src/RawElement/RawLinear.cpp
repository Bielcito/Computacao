#include "../../inc/RawElement/RawLinear.h"

void RawLinear::set_spread_type(const std::string& spread) { this->spread = spread; }
void RawLinear::set_p0(const Vec2& p) { this->p0 = p; }
void RawLinear::set_p1(const Vec2& p) { this->p1 = p; }

void RawLinear::push_stop(double s, const Color_v& c) 
{
	stops.push_back( std::pair<double,Color_v>(s,c) );
}

Paint* RawLinear::preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf)
{
	// Você deve montar aqui uma transformação que leva
	// p0 para a origem e p1 para <1,0>. Isso envolve uma
	// translação -p0, uma rotação que leva p1 para o eixo
	// x e uma escala que leva p1 para <1,0>.
	//
	// Não esqueça de levar em consideração a transformação
	// do paint!
	//
	// Você vai construir essa matrix e passar ela como parâmetro
	// para o objeto Linear
	Matrix3 world2canonical = Matrix3::identity();

	return new Linear(world2canonical, stops, Spread::spread_func_from_str(spread));
}