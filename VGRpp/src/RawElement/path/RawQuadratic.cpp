#include "../../../inc/RawElement/path/RawQuadratic.h"

void RawQuadratic::cut_at(double t0, double t1, Quadratic& out)
{
	//This is the blossom method for bézier cut
	Vec2 _p0;
	_p0.setX( Numeric::lerp2(t0, t0, p0.x(), p1.x(), p2.x()) );
	_p0.setY( Numeric::lerp2(t0, t0, p0.y(), p1.y(), p2.y()) );
	out.set_p0( _p0 );

	Vec2 _p1;
	_p1.setX( Numeric::lerp2(t0, t1, p0.x(), p1.x(), p2.x()) );
	_p1.setY( Numeric::lerp2(t0, t1, p0.y(), p1.y(), p2.y()) );
	out.set_p1( _p1 );
	
	Vec2 _p2;
	_p2.setX( Numeric::lerp2(t1, t1, p0.x(), p1.x(), p2.x()) );
	_p2.setY( Numeric::lerp2(t1, t1, p0.y(), p1.y(), p2.y()) );
	out.set_p2( _p2 );
}

RawQuadratic::RawQuadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

std::string RawQuadratic::prim2str()
{
	std::stringstream out;
	out<<"RawQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]";
	return out.str();
}

void RawQuadratic::transform(const Matrix3& t)
{
	p0 = t.apply( p0.homogeneous() ).euclidean();
	p1 = t.apply( p1.homogeneous() ).euclidean();
	p2 = t.apply( p2.homogeneous() ).euclidean();
}

void RawQuadratic::preprocess(std::vector<Primitive*>& holder)
{
	// Essa é a parte mais difícil de renderizar uma curva.
	//
	// Para monotonizar: comece calculando em que pontos t1
	// e t2 a curva muda de sinal. Lembre-se que é simplesmente
	// dF/dt = 0, e que temos duas funções de uma variável:
	// ( x(t), y(t) ). Como cada função é quadrática, a derivada
	// será uma função linear (at+b).
	Vec2 a, b; double t[] = {0.0, -1.0, -1.0, 1.0};

	// t deve conter os pontos de mudança de sinal em t[1] e t[2].
	// Agora, invoque a função cut_at() para cortar a curva em
	// quantas partes for necessário. Teremos no máximo três novas
	// curvas -> [t0,t1], [t1,t2], [t2,t3]
	// 
	// Crie dinamicamente um ponteiro para objeto Quadratic usando
	// new e coloque no vetor holder usando holder.push_back(). 
	// Note que Quadratic herda de Primitive, então podemos fazer
	// isso!
	//
	// Se tudo der certo nessa parte, vocÊ deverá ver um quadradinho
	// colorido no lugar da curva.
}