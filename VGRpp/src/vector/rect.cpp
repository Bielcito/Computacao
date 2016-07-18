#include "../../inc/vector/rect.h"

void Rect::setLeftBottom(const Vec2& v)
{
	left_bottom = v;
}

void Rect::setRightTop(const Vec2& v)
{
	top_right = v;
}

Rect::Rect(const Vec2& left_bottom, const Vec2& top_right)
{
	this->left_bottom = left_bottom;
	this->top_right = top_right;
}

Rect::Rect(double x0, double y0, double x1, double y1)
{
	left_bottom.setX(x0); left_bottom.setY(y0);
	top_right.setX(x1); top_right.setY(y1);
}

Rect::Rect()
{
	Rect(0.0, 0.0, 0.0, 0.0);
}