#ifndef SCENE_H
#define SCENE_H


#include "../myengine_api.h"
#include <iostream>
#include <list>
#include <string>

namespace Inaba
{
	class Renderer;
	class Entity2D;

	class MYENGINE_API Scene
	{
	private:
		std::list<Entity2D*> _entities;
	public:
		Scene();
		 bool Init();
		 bool Frame(Renderer&);
		 bool deInit();
		 bool getEntity(Entity2D*, std::string);
		 void AddEntity(Entity2D*);
	};
}




#endif