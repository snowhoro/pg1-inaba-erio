#ifndef QUAD_H
#define QUAD_H

#include "xMath.h"
#include "RenderTypes.h"
#include "myengine_api.h"

namespace Inaba
{
	class Renderer;

	class MYENGINE_API Quad
	{
		public:
			Quad();
			~Quad();
			
			void setPos(float,float);
			void setRotation(float);
			void setScale(float);

			float posX() const;
			float posY() const;
			float rotation() const;
			float scale() const;

			void Draw(Renderer&) const;
		private:
			float _posX, _posY;
			float _rotation;
			float _scale;
			ColorVertex* _vertex;
			Matrix _transformationMatrix;

			void UpdateLocalTransformation();

	};
}

#endif