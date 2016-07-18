#ifndef _RENDER_H_
#define _RENDER_H_

#include <vector>
#include "RawElement/RawElement.h"
#include "vector/rect.h"
#include "vector/matrix3.h"
#include "element/element.h"
#include "color.h"
using Color::ColorRGBA;

class Render
{
private:
	//render pool: contains all objects which must be rendered, in order
	std::vector<Element*> render_pool;

	//viewport transformation for this window
	Matrix3 viewport_t;
	Vec2 viewport_size;

	//Background color (define this after inside .2d file)
	ColorRGBA bg_color;

	//handle window and keyboard input. Return TRUE if we must quit.
	bool handle_input();

	//Render class is a Singleton
	static Render* render_ptr;
	Render();

public:
	~Render();

	//take raw objects, preprocess and store in pool
	int preprocess(std::vector<RawElement>& raw, const Rect& window, const Vec2& viewport, const Matrix3& scene_t);

	//creates window, draw everything inside pool until we quit
	void run();

	//returns the only instance of Render class
	static Render* instance() {
		if(!Render::render_ptr)
			Render::render_ptr = new Render();
		return Render::render_ptr;
	}
};

#endif