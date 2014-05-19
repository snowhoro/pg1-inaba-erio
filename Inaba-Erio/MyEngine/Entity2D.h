#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "xMath.h"
#include "RenderTypes.h"
#include "myengine_api.h"

namespace Inaba
{
	class Renderer;

	class MYENGINE_API Entity2D
	{
		public:
			Entity2D();
			~Entity2D();
			
			void setPos(float,float);
			void setRotation(float);
			void setScale(float);

			float posX() const;
			float posY() const;
			float rotation() const;
			float scale() const;

			void Draw(Renderer&) const;

		protected:
			float _posX, _posY;
			float _rotation;
			float _scale;

			Matrix _transformationMatrix;

			void UpdateLocalTransformation();

	};
}

#endif