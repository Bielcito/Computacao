#include "../../../inc/element/path/rquadratic.h"

void RQuadratic::setAABB()
{
	min.setX( p0.x() < p2.x() ? p0.x() : p2.x());
	min.setY( p0.y() < p2.y() ? p0.y() : p2.y());

	max.setX( p0.x() > p2.x() ? p0.x() : p2.x());
	max.setY( p0.y() > p2.y() ? p0.y() : p2.y());
}

void RQuadratic::recompute_param()
{
	setAABB();
	dy = Numeric::sign( p2.y() - p0.y() );
}

RQuadratic::RQuadratic(const Vec2& p0, const Vec3& p1, const Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;

	recompute_param();
}

void RQuadratic::set_p0(const Vec2& p) { this->_p0 = p; this->p0 = p; recompute_param(); }
void RQuadratic::set_p1(const Vec3& p) { this->_p1 = p; this->p1 = p; recompute_param(); }
void RQuadratic::set_p2(const Vec2& p) { this->_p2 = p; this->p2 = p; recompute_param(); }

//-----------------------------------------
//---------- FROM PRIMITIVE.h -------------
//-----------------------------------------
std::string RQuadratic::prim2str()
{
	std::stringstream ss;
	ss<<"RQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<", "<<p1.w()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]";
	return ss.str();
}

void RQuadratic::transform(const Matrix3& t)
{
	//We can't do anything here, because monotonization is not
	//invariant to transformations! i.e. transforming the curve
	//here would make it lose the monotonic property.
}

//Returns ZERO if the ray casted in the x direction
//does not intersects with the primitive; if there is 
//such an intersection, returns -1 or +1 depending on
//the direction the primitive is going (down or up) 
int RQuadratic::to_the_left(const Vec2& p)
{
	// Essa vai ser um pouco mais difícil, mas você pode colar
	// do método para curvas quadráticas integrais. Retorne zero
	// se não houver interseção e retorne DY (+1/-1) se houver.
	//
	// Você vai calcular o ponto de interseção entre a curva racional
	// e a linha horizontal com origem p.y(), igual às curvas integrais,
	// mas lembre que o ponto é da forma [x.w y.w w], então para achá-lo
	// na forma [x y] você deve dividir x.w e y.w por w.
	//
	// Você deve achar numericamente a interseção usando um método
	// de biseção ou Newton-Raphson, por exemplo. Se você não quiser
	// fazer seu próprio método, veja a função Numeric::RC_find_root(),
	// que implementa um método de biseção bem simples (e ineficiente).



	return false;
}