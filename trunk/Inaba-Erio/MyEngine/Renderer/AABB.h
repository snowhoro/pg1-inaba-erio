#ifndef AABB_H
#define AABB_H

#include "RenderTypes.h"
#include <d3dx9.h>

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
		void setBounds(TextureCoordVertex* vertices,int numVertex);
		float getWidth();
		float getHeight();
		float getDepth();
		
		
		D3DXVECTOR3 getCenter();
};

}
#endif