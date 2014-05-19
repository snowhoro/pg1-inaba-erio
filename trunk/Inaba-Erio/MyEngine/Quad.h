#ifndef QUAD_H
#define QUAD_H

#include "Entity2D.h"
#include "xMath.h"
#include "RenderTypes.h"
#include "myengine_api.h"

namespace Inaba
{
	class Renderer;

	class MYENGINE_API Quad : public Entity2D
	{
		public:
			Quad();
			~Quad();

			void Draw(Renderer&) const;
		private:
			ColorVertex* _vertex;
	};
}

#endif