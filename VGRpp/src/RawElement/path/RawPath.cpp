#include "../../../inc/RawElement/path/RawPath.h"


void RawPath::push_primitive(RawPrimitive* prim) 
{
	if(prim) this->primitives.push_back(prim);
}

Shape* RawPath::preprocess(const Matrix3& model_xf, const Matrix3& scene_xf) 
{
	Path *p = new Path;

	//transform raw primitive
	for(auto p = primitives.begin(); p != primitives.end(); ++p)
		(*p)->transform(scene_xf * model_xf);

	//preprocess each primitive
	std::vector<Primitive*> holder;
	for(int i = 0; i < primitives.size(); i++)
		primitives[i]->preprocess(holder);

	//push each preprocessed primitive to Path
	for(int i = 0; i < holder.size(); i++)
		p->push_primitive( holder[i] );

	return p;
}