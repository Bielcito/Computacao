#ifndef _RAW_TEXTURE_H_
#define _RAW_TEXTURE_H_

#include "./RawPaint.h"
#include "../element/texture.h"
#include "../spread.h"
#include <SDL_image.h>
#include <SDL/SDL.h>

using Spread::spread_func;

#include <iostream>
using std::cout;
using std::endl;

class RawTexture : public RawPaint
{
private:
	std::string spread, url;

public:
	//----------------------------------
	//--------- Access methods ---------
	//----------------------------------
	void set_spread_type(const std::string& spr);
	void set_image_url(const std::string& url);

	//-----------------------------------
	//--------- From RawPaint.h ---------
	//-----------------------------------
	Paint* preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf) override;
};

#endif