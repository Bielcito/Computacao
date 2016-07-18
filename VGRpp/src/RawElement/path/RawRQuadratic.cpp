#include "../../../inc/RawElement/path/RawRQuadratic.h"

void RawRationalQuadratic::compute_maxima(double x0, double x1, double w, double x2, double& r1, double& r2)
{
	double a = 2*(-1 + w)*(x0 - x2);
	double b = 2*(x0 - 2*w*x0 + 2*x1 - x2);
	double c = 2*(w*x0 - x1);

	Numeric::quadratic(a, b, c, r1, r2);
}

void RawRationalQuadratic::cut_at(double a, double b, RQuadratic& out)
{
	//Cut curve at a, b
	double u0, v0, r0, u1, v1, r1, u2, v2, r2;
	u0 = Numeric::lerp2(a, a, p0.x(), p1.x(), p2.x() );
	v0 = Numeric::lerp2(a, a, p0.y(), p1.y(), p2.y() );
	r0 = Numeric::lerp2(a, a, 1, p1.w(), 1);
	u1 = Numeric::lerp2(a, b, p0.x(), p1.x(), p2.x() );
	v1 = Numeric::lerp2(a, b, p0.y(), p1.y(), p2.y() );
	r1 = Numeric::lerp2(a, b, 1, p1.w(), 1);
	u2 = Numeric::lerp2(b, b, p0.x(), p1.x(), p2.x() );
	v2 = Numeric::lerp2(b, b, p0.y(), p1.y(), p2.y() );
	r2 = Numeric::lerp2(b, b, 1, p1.w(), 1);

	//canonize final arc
	double ir0 = 1.0/r0, ir2 = 1.0/r2;
	double ir1 = 1.0/sqrt(r0*r2);

	u0 *= ir0; u1 *= ir1; u2 *= ir2;
	v0 *= ir0; v1 *= ir1; v2 *= ir2;
	r0 *= ir0; r1 *= ir1; r2 *= ir2;

	out.set_p0( Vec2(u0, v0) );
	out.set_p1( Vec3(u1, v1, r1) );
	out.set_p2( Vec2(u2, v2) );
}

RawRationalQuadratic::RawRationalQuadratic(const Vec2& p0, const Vec3& p1, const Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

std::string RawRationalQuadratic::prim2str()
{
	std::stringstream ss;
	ss<<"RawRQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<", "<<p1.w()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]"<<std::endl;
	return ss.str();
}

void RawRationalQuadratic::preprocess(std::vector<Primitive*>& holder)
{
	// Este laboratório será bem parecido com o de curvas quadráticas
	// integrais, mas algumas fórmulas mudam e também o número máximo
	// de curvas que conseguimos no fim.
	//
	// Não esqueça que o ponto de controle lido está na forma [x y w], 
	// isto é: temos a localização do ponto no espaço euclidiano do modelo
	// e o seu peso. Isso significa então que antes de fazer quaisquer
	// operações, o ponto deve ser PROJETADO (posto na forma [x.w y.w w]).
	//
	// Lembre também que só o ponto de controle está num plano diferente de
	// w = 1, então os outros pontos são armazenados como Vec2 e não Vec3.
	//
	// Derivar uma quadrática racional é a derivada de uma razão de polinômios
	// (reveja o slide). No fim igualamos o numerador do polinômio derivado a zero
	// e percebemos que é necessário resolver uma equação quadrática: isso significa
	// que podemos ter duas raízes (= pontos de máximo) para y(t) e duas raízes
	// (= pontos de máximo) para x(t), então é possível ter 5 curvas monótonas
	// ao fim! A função para cortar a Bézier racional é idêntica e já está implementada,
	// então não precisa se preocupar com isso.
	//
	// Da mesma forma que no exercício de quadráticas integrais, você deve
	// colocar os ponteiros para as novas curvas (RQuadratic*) no vetor holder
	// usando holder.push_back().
}

void RawRationalQuadratic::transform(const Matrix3& t)
{
	p0 = t.apply( p0.homogeneous() ).euclidean();
	p2 = t.apply( p2.homogeneous() ).euclidean();

	//for transformation purposes, the w coordinate
	//is just the weight of the point; it is not
	//projected yet
	double weight = p1.w();
	p1 = t.apply( Vec3(p1.x(), p1.y(), 1.0) );
	p1.setW(weight);
}