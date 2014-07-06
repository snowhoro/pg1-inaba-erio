#include "Scene.h"
#include "../Entity2D/Entity2D.h"

using namespace Inaba;

Scene::Scene()
//: _entities(new std::list<Entity2D*>)
{	
}

bool Scene::Init()
{
	//IMPORT 
	return true;
}

bool Scene::Frame(Renderer &renderer)
{
	if(_entities.empty())
		return false;
	
	std::list<Entity2D*>::iterator iter;
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

bool Scene::getEntity(Entity2D *entity, std::string name)
{
	if(_entities.empty())
		return false;
	
	std::list<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		if((*iter)->name() == name)
		{
			entity = *iter;
			return true;
		}
	}

	return false;
}

void Scene::AddEntity(Entity2D* entity)
{
	_entities.push_back(entity);
}