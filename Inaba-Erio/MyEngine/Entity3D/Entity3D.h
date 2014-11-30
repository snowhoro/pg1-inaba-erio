#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "../Renderer/xMath.h"
#include "../Renderer/RenderTypes.h"
#include "../Renderer/AABB.h"
#include "../myengine_api.h"
#include <d3dx9.h>
#include <string>
#include "../Physics/RigidBody.h"

namespace Inaba
{
	class Renderer;
	class Timer;
	class Node;
	

	class MYENGINE_API Entity3D
	{
		public:
			Entity3D();
			~Entity3D();
			
			const RigidBody* getRigidbody() const { return _rigidBody; };
			RigidBody* getRigidbody(){ return _rigidBody; };

			void setPos(float,float,float);
			void setRotation(float,float,float);
			void setScale(float,float,float);

			float posX() const;
			float posY() const;
			float posZ() const;
			float rotX() const;
			float rotY() const;
			float rotZ() const; 
			float scaleX() const;
			float scaleY() const;
			float scaleZ() const;
			//void Draw(Renderer&) const; 

			float prevPosX() const;
			float prevPosY() const;
			float prevPosZ() const;

			enum CollisionResult{
				CollisionVertical,
				CollisionHorizontal,
				NoCollision
			};

			CollisionResult checkCollision(Entity3D&) const;
			void drawAABB (Renderer&) const;
			void returnToPos(float, float, float);
			virtual void Draw(Renderer&) const = 0;
			virtual void Update(Timer&);
			std::string name() const;
			AABB* getAABB(); 
			void setName(std::string);
			void UpdateTransformation();
			void SetParent(Node*);
			void UpdateAABB();
			Node* GetParent();
			Matrix GetTranformationMatrix();	
			

		protected:
			float _posX, _posY, _posZ,_prevPosX, _prevPosY, _prevPosZ;
			float _rotX, _rotY, _rotZ;
			float _scaleX;
			float _scaleY;
			float _scaleZ;
			std::string _name; 
			Node* _parent;
			Matrix _transformationMatrix;
			Matrix _worldTransformationMatrix;
			void UpdateLocalTransformation();
			AABB* _AABB;
			RigidBody  *_rigidBody;
	};
}

#endif