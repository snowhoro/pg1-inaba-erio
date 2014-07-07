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
	class MYENGINE_API Scene
	{
	private:
		std::vector<Entity2D*> _entities;
	public:
		Scene();
		 bool Init(Renderer&);
		 bool Frame(Renderer&);
		 bool deInit();
		 Entity2D* getEntity(std::string);
		 void AddEntity(Entity2D*);
	};
}




#endif