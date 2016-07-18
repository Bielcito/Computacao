#ifndef _RAW_LINE_H_
#define _RAW_LINE_H_

#include "../../vector/vector2.h"
#include "./RawPrimitive.h"
#include "../../element/path/line.h"
#include <string>
#include <sstream>

class RawLine : public RawPrimitive
{
private:
	Vec2 p1, p2;

public:
	RawLine(Vec2 p1, Vec2 p2);
	std::string prim2str() override;

	void preprocess(std::vector<Primitive*>& holder) override;
	void transform(const Matrix3& t) override;
};

#endif