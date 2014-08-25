#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "../Renderer/xMath.h"
#include "../Renderer/RenderTypes.h"
#include "../myengine_api.h"
#include <string>
namespace Inaba
{
	class Renderer;
	class Timer;

	class MYENGINE_API Entity3D
	{
		public:
			Entity3D();
			~Entity3D();
			
			void setPos(float,float);
			void setPos(float,float,float);
			void setRotation(float);
			void setScale(float,float);

			float posX() const;
			float posY() const;
			float posZ() const;
			float rotation() const;
			float scaleX() const;
			float scaleY() const;
			//void Draw(Renderer&) const; 

			float prevPosX() const;
			float prevPosY() const;

			enum CollisionResult{
				CollisionVertical,
				CollisionHorizontal,
				NoCollision
			};

			CollisionResult checkCollision(Entity3D&) const;
			void drawAABB (Renderer&) const;
			void returnToPos(float, float);
			virtual void Draw(Renderer&) const = 0;
			virtual void Update(Timer&) = 0;
			std::string name() const;
			void setName(std::string);
		protected:
			float _posX, _posY, _posZ,_prevPosX, _prevPosY, _prevPosZ;
			float _rotation;
			float _scaleX;
			float _scaleY;
			std::string _name; 

			Matrix _transformationMatrix;

			void UpdateLocalTransformation();

	};
}

#endif