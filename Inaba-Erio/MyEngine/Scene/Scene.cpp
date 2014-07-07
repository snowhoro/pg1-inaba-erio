#include "Scene.h"
#include "../Entity2D/Entity2D.h"
#include "../Entity2D/Quad.h"
#include "../Entity2D/Sprite.h"
#include "../Entity2D/Animation.h"
#include "../Timer/Timer.h"
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

bool Scene::Frame(Renderer &renderer,Timer &timer)
{
	if(_entities.empty())
		return false;
	
	std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		(*iter)->Update(timer);
		(*iter)->Draw(renderer);
	}

	return true;
}

bool Scene::deInit()
{
	//delete
	return true;
}

bool Scene::getEntity(Sprite **ent ,std::string name)
{
	if(_entities.empty())
		return NULL;

	for(int i=0; i < _entities.size(); i ++){
		if(_entities[i]->name() == name){
			*ent = (Sprite*)_entities[i];
			return true;
		}
	}
	return false;
}

bool Scene::getEntity(Quad **ent ,std::string name)
{
	if(_entities.empty())
		return NULL;

	for(int i=0; i < _entities.size(); i ++){
		if(_entities[i]->name() == name){
			*ent = (Quad*)_entities[i];
			return true;
		}
	}
	return false;
}

void Scene::AddEntity(Entity2D* entity)
{
	_entities.push_back(entity);
}