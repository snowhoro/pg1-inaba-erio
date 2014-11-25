/*
#ifndef PHYSICS_H
#define PHYSICS_H


#include "../myengine_api.h"



namespace Inaba
{	
	class hkVisualDebugger;
	class hkpPhysicsContext;
	class hkpWorld;
	class hkpRigidBody;

	class MYENGINE_API Physics
	{

		private:
			Physics* _instance;
			hkpWorld* _world;
			hkVisualDebugger* _vdb;
			hkpPhysicsContext* _physicsContext;
			void InitPhysics();
			void DeInitPhysics();


		public:
			Physics();
			~Physics();
			static Physics* GetInstance();
			hpkWorld* GetWorld();
			
	};
}
#endif
*/