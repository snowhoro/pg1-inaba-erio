#ifndef AABB_H
#define AABB_H

#include "RenderTypes.h"

namespace Inaba
{

class MYENGINE_API AABB
{
	private:
		TextureCoordVertex _min;
		TextureCoordVertex _max;
	public:
		AABB();
		~AABB();
		void setBound(TextureCoordVertex* vertices,int numVertex);

		
};

}
#endif