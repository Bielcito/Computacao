#include "../../../inc/element/path/path.h"

//Applies transformation to all primitives in path
void Path::transform_primitives()
{
	Matrix3 t = scene_xf * model_xf;
	for(auto p = primitives.begin(); p != primitives.end(); ++p)
		(*p)->transform(t);
}

//----------------------------------------
//------------ ACCESS METHODS ------------
//----------------------------------------
void Path::push_primitive(Primitive* p) 
{
	if(p) primitives.push_back(p);
}

void Path::set_modelxf(const Matrix3& model_xf) 
{
	this->model_xf = model_xf;
	transform_primitives();
}

//--------------------------------------
//------------ FROM SHAPE.H ------------
//--------------------------------------
void Path::set_scenexf(const Matrix3& scene_xf) 
{
	this->scene_xf = scene_xf;
	transform_primitives();
}

bool Path::is_inside(double x, double y) 
{
	Vec2 point(x,y);
	int winding_number = 0;

	for(auto p = this->primitives.begin(); p != this->primitives.end(); ++p)
		winding_number += (*p)->to_the_left(point);
	
	return winding_number != 0;
}