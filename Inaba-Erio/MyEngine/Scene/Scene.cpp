#include "Scene.h"
#include "../Entity2D/Entity2D.h"
#include "../Entity2D/Quad.h"
#include "../Entity2D/Sprite.h"
#include "../Entity2D/Animation.h"

using namespace Inaba;

Scene::Scene()
//: _entities(new std::list<Entity2D*>)
{	
}

bool Scene::Init(Renderer &renderer)
{
	/*if(_entities.empty())
		return false;*/
	
	/*std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		(*iter)->Draw(renderer);
	}*/
	return true;
}

bool Scene::Frame(Renderer &renderer)
{
	if(_entities.empty())
		return false;
	
	std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		(*iter)->Draw(renderer);
	}

	return true;
}

bool Scene::deInit()
{
	//delete
	return true;
}

Entity2D* Scene::getEntity(std::string name)
{
	if(_entities.empty())
		return false;
	
	for(int i=0; i < _entities.size(); i ++){
		if(_entities[i]->name() == name){
			return _entities[i];
			
		}
	}
	/*std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		if((*iter)->name() == name)
		{
			//((Entity2D*)*iter);
			//entity = _entities.
			entity = (Quad*)(*iter);
			return true;
		}
	}*/
	return false;
}

/*Sprite* Scene::getEntity(std::string name)
{
	if(_entities.empty())
		return false;
	
	std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		if((*iter)->name() == name)
		{
			return (Sprite*)(*iter);
		}
	}

	return false;
}*/

void Scene::AddEntity(Entity2D* entity)
{
	_entities.push_back(entity);
}