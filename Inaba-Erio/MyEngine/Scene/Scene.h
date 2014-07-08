#ifndef SCENE_H
#define SCENE_H

#include "../myengine_api.h"
#include <iostream>
#include <vector>
#include <string>

namespace Inaba
{
	class Renderer;
	class Entity2D;
	class Quad;
	class Sprite;
	class Animation;
	class Timer;
	class MYENGINE_API Scene
	{
	private:
		std::vector<Entity2D*> _entities;
	public:
		Scene();
		~Scene();
		 bool Init(Renderer&);
		 bool Frame(Renderer&,Timer&);
		 bool deInit();
		 bool getEntity(Sprite** ent ,std::string name);
		 bool getEntity(Quad** ent ,std::string name);
		 void AddEntity(Entity2D*);
	};
}




#endif