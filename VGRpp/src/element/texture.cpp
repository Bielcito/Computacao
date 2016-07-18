#include "../../inc/element/texture.h"

//------------------------------------
//------------ Internal --------------
//------------------------------------
#define ROUND(x) ((int)((x)+0.5))

static const int CHANNEL_3 = 24;
static const int CHANNEL_4 = 32;

static ColorRGBA get_pixel_in_surface(int i, int j, SDL_Surface *image)
{
	//start inverting y-axis
	i = image->h - i - 1;

	//WARNING: Terrible things happen to those
	//who change this code. Thou shalt not attempt it.
	if( image->format->BitsPerPixel == CHANNEL_3 )
	{
		//In this case, pixels are packed as straight
		//triples of Uint8. This means that pixel in
		//column j is actually placed in byte 3*j
		j *= 3;

		//we get the first byte of the triple.
		//->pitch returns the length of a line in BYTES,
		//and that's why we use it here (1 Uint8 = 1 byte).
		Uint8* pxl8 = (Uint8*)image->pixels;
		Uint8* p = &pxl8[i*image->pitch + j];
		
		//here we "build" the final pixel
		Uint32 out = 0xFF000000;
		out |= (p[0] << 16);
		out |= (p[1] << 8);
		out |= p[2];

		return out;
	}
	else if( image->format->BitsPerPixel == CHANNEL_4 )
	{	
		//For Uint32 arrays, each element is 4 bytes, and is
		//a pixel itself, so we use ->w to get the vertical
		//displacement, as ->w is the number of pixels in a line
		Uint32* pxl32 = (Uint32*)image->pixels;
		return pxl32[i*image->w + j];
	}
}

//------------------------------------------
//------------ From Texture.h --------------
//------------------------------------------
Texture::Texture(SDL_Surface* image, spread_func spread, const Matrix3& scene2tex)
{
	this->image = image;
	this->spread = spread;
	this->scene2tex = scene2tex;
}

//-----------------------------------
//--------- From Texture.h ----------
//-----------------------------------
ColorRGBA Texture::sample(double x, double y)
{
	// Comece mapeando o ponto (x,y) para o espaço da textura.
	// Depois, use a função this->spread() mapeie o ponto no
	// retângulo [0,1] x [0,1].
	//
	// Mapeie o ponto do retângulo [0,1] x [0,1] para um ponto
	// na imagem this->image. Você vai encontrar um valor real 
	// como 120.7, por exemplo, mas precisamos de um valor inteiro
	// para poder acessar o pixel da imagem. Aí é que entra a fase 
	// de interpolação: Nearest-Neighbour, em que você só arredonda
	// o valor para o inteiro mais próximo; Interpolação Bilinear,
	// em que você usa os 4 pixels mais próximos para interpolar
	// o valor final, etc. 

	int j = 0;
	int i = 0;

	return get_pixel_in_surface(i, j, this->image);
}