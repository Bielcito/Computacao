#include "../../../inc/element/path/quadratic.h"
#include "../../../inc/vector/numeric.h"
#include <iostream>
using namespace std;

void Quadratic::setAABB()
{
	min.setX( p0.x() < p2.x() ? p0.x() : p2.x() );
	min.setY( p0.y() < p2.y() ? p0.y() : p2.y() );

	max.setX( p0.x() > p2.x() ? p0.x() : p2.x() );
	max.setY( p0.y() > p2.y() ? p0.y() : p2.y() );
}

void Quadratic::setDY()
{
	int diff = p2.y() - p0.y();
	if(diff > 0) dy = +1;
	else if(diff < 0) dy = -1;
	else dy = 0;
}

void Quadratic::recompute_param()
{
	setAABB();
	setDY();
}

Quadratic::Quadratic() {}

Quadratic::Quadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->_p0 = p0;
	this->_p1 = p1;
	this->_p2 = p2;

	recompute_param();
}

void Quadratic::set_p0(const Vec2& _p0) { this->_p0 = _p0; this->p0 = _p0; recompute_param(); }
void Quadratic::set_p1(const Vec2& _p1) { this->_p1 = _p1; this->p1 = _p1; recompute_param(); }
void Quadratic::set_p2(const Vec2& _p2) { this->_p2 = _p2; this->p2 = _p2; recompute_param(); }

std::string Quadratic::prim2str() 
{
	std::stringstream ss;
	ss<<"Quadratic[("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<"), "<<dy<<"]";
	return ss.str();
}

void Quadratic::transform(const Matrix3& t) 
{
	//We can't do anything here, because monotonization is not invariant under
	//any transformations!
}

int Quadratic::to_the_left(const Vec2& p) 
{
	if(min.y() <= p.y() && p.y() < max.y())
	{
		if(p.x() <= min.x()) return dy;
		if(p.x() > max.x()) return 0;

		Numeric aux;
		double a, b;
		aux.quadratic( 
						(p0.y() - 2 * p1.y() + p2.y()), 
						(-2 * p0.y() + 2 * p1.y()), 
						(p0.y() - p.y()), 
						a, 
						b
					);

		double t = (a >= 0 && a <= 1) ? a : b;
		double x_inter = Numeric::bezier2_at(t, p0.x(), p1.x(), p2.x());

		// Comece verificando em que parâmetro t y(t) é igual
		// a p.y(). Depois, ache x(t) e retorne +1/-1 se
		// p.x() estiver à esquerda.
		//
		// Armazene x(t) em x_inter!
		//
		// Lembre que no cabeçalho inc/vector/numeric.h tem algumas funções
		// que podem ser úteis. Verifique!

		return (p.x() <= x_inter) ? dy : 0;
	}
	return 0;
}