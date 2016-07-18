#ifndef _RAW_SOLID_H_
#define _RAW_SOLID_H_

#include "../color.h"
#include "RawPaint.h"
#include "../vector/matrix3.h"
#include "../element/solid.h"
using Color::ColorChnl;
using Color::ColorRGBA;

class RawSolid : public RawPaint
{
private:
	ColorChnl R_, G_, B_, A_;

public:
	RawSolid();
	RawSolid(ColorChnl R, ColorChnl G, ColorChnl B, ColorChnl A);

	//----------------------------
	//------ From RawPaint -------
	//----------------------------
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_xf) override;
};

#endif