#include "../../inc/RawElement/RawRadial.h"

void RawRadial::set_spread_type(const std::string& spread) { this->spr = spread; }
void RawRadial::set_center(const Vec2& p) { this->center = p; }
void RawRadial::set_focus(const Vec2& p) { this->focus = p; }
void RawRadial::set_radius(double r) { this->radius = r; }

void RawRadial::push_stop(double s, const Color_v& color) 
{ 
	this->stops.push_back( std::pair<double,Color_v>(s, color) ); 
}

//-------------------------------------
//---------- From RawPaint.h ----------
//-------------------------------------
Paint* RawRadial::preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf)
{
	// Assim como no gradiente linear, você vai construir uma transformação
	// que mapeia um ponto para um espaço de gradiente radial canônico:
	// Translade o foco para a origem, rotacione para por o centro no eixo x,
	// escalone para o raio ser 1. Novamente, não esqueça da transformação do paint!
	Matrix3 canonical_grad = Matrix3::identity();

	//ATENÇÃO: Eu não sei exatamente o que o SVG/PS especifica para o caso em que o foco
	//cai fora do círculo. Vamos só assumir que se ele estiver na borda, vamos trazê-lo
	// pra borda.
	if( center.x() > 1.0) center.setX(1.0);

	return new Radial( Spread::spread_func_from_str(spr), center.x(), canonical_grad, stops );
}