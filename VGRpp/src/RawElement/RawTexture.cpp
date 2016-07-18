#include "../../inc/RawElement/RawTexture.h"

#define img_flags (IMG_INIT_PNG | IMG_INIT_JPG)

void RawTexture::set_spread_type(const std::string& spr) { this->spread = spr; }
void RawTexture::set_image_url(const std::string& url) { this->url = url; }

//-----------------------------------
//--------- From RawPaint.h ---------
//-----------------------------------
Paint* RawTexture::preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf)
{
	//TODO: Maybe this is not good. It would be nice if we could
	//transform in the order: scene -> object -> texture, but
	//here we have no access to object system coordinates. We'll
	//just assume the user knows what he's doing and assume paint_xf
	//sends the pixel from scene space to texture space.
	Matrix3 scene2tex = (scene_xf * paint_xf).inv();

	//initialize SDL image drive. TODO: MUST DROP THIS POINTER AFTER
	if( !IMG_Init(img_flags) )
		cout<<"Error while initialize SDL Image!"<<endl;

	//load image
	SDL_Surface *image = IMG_Load( this->url.c_str() );

	if( !image )
		cout<<"Error while loading image: "<<IMG_GetError()<<endl;

	return new Texture(image, Spread::spread_func_from_str(this->spread), scene2tex );
}