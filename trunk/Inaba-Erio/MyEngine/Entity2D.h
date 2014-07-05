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
			void setScale(float,float);

			float posX() const;
			float posY() const;
			float rotation() const;
			float scaleX() const;
			float scaleY() const;
			void Draw(Renderer&) const; 

			float prevPosX() const;
			float prevPosY() const;

			enum CollisionResult{
				CollisionVertical,
				CollisionHorizontal,
				NoCollision
			};

			CollisionResult checkCollision(Entity2D&) const;
			void drawAABB (Renderer&) const;
			void returnToPos(float, float);

		protected:
			float _posX, _posY,_prevPosX, _prevPosY;
			float _rotation;
			float _scaleX;
			float _scaleY;

			Matrix _transformationMatrix;

			void UpdateLocalTransformation();

	};
}

#endif