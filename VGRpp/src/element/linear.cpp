#include "../../inc/element/linear.h"

Linear::Linear(const Matrix3& world2canonical, const std::vector< std::pair<double,Color_v> >& stops, spread_func spr_func)
{
	this->world2canonical = world2canonical;

	//OMG! move semantics. I hope this is the right way to use it
	//this should be safe because Stops in RawLinear object won't
	//be used anymore.
	this->stops = std::move(stops);

	this->spr_func = spr_func;
}

ColorRGBA Linear::sample(double x, double y)
{
	// Comece mapeando o ponto (x,y) para o espaço
	// canônico usando a matrix world2canonical.

	// Depois, compute a projeção deste ponto no vetor
	// P1-P0 (que no fim é o vetor <1,0> ).
	
	// Isso vai te retornar um valor real. Esse valor
	// deve ser tratado pela função de espalhamento
	// spr_func.

	// Depois disso, você deve percorrer a rampa de cores
	// e encontrar a cor a retornar. Num primeiro momento,
	// basta retornar a cor mais próxima, depois você pode
	// tentar tomar as duas cores mais próximas à esquerda
	// e à direita e realizar uma interpolação linear.

	// Lembre-se que as cores em uma struct Color_v são
	// armazenadas num intervalo [0,1]! 
	Color_v out = {1.0, 1.0, 1.0, 1.0};

	return Color::rgba_from_colorv(out);
}	