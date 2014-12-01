#include "Scene.h"
#include "../Entity2D/Entity2D.h"
#include "../Entity3D/Entity3D.h"
#include "../Entity2D/Quad.h"
#include "../Entity2D/Sprite.h"
#include "../Entity2D/Animation.h"
#include "../Entity3D/Mesh.h"
#include "../Entity3D/Node.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"
#include "../Renderer/Renderer.h"
#include "../Game.h"

using namespace Inaba;

Scene::Scene()
{	
}

bool Scene::deInit()
{
	if(_entities.empty())
		return true;

	for(int i=0; i < _entities.size(); i ++)
	{
		delete _entities[i];
		_entities[i] = NULL;
	}	
	_entities.clear();

	return true;
}

bool Scene::Draw(Renderer &renderer,Timer &timer)
{
	if(_entities.empty() && _entities3D.empty())
		return false;
	
	std::vector<Entity2D*>::iterator iter;
	for(iter = _entities.begin(); iter != _entities.end(); iter++)
	{
		(*iter)->Update(timer);
		(*iter)->Draw(renderer);
	}


	if (!_entities3D.empty()){
		((Node*)(_entities3D[0]))->UpdateTransformation();
		((Node*)(_entities3D[_entities3D.size() -1]))->UpdateAABB();
	}

	std::vector<Entity3D*>::iterator iter2;
	for(iter2 = _entities3D.begin(); iter2 != _entities3D.end(); iter2++)
	{
		(*iter2)->Update(timer);
		CheckDraw(renderer,*(*iter2));
	}

	return true;
}

bool Scene::CheckDraw(Renderer& renderer,Entity3D& entity) {
	
	int r = renderer.getCamera()->checkCollisionAABB(&entity);

	if(r == Camera::INSIDE)
		entity.Draw(renderer);
	else if (r == Camera::INTERSECT){
        Inaba::Node* child = dynamic_cast<Inaba::Node*>(&entity);
        if(child){ //
			for(list<Entity3D*>::iterator it = child->getChilds().begin(); it != child->getChilds().end(); it++) {
				CheckDraw(renderer,entity);
			}
		}
		else{
			entity.Draw(renderer);                
		}
	}
	return true;
}

bool Scene::getEntity(Sprite **ent ,std::string name)
{
	if(_entities.empty())
		return false;

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
		return false;

	for(int i=0; i < _entities.size(); i ++){
		if(_entities[i]->name() == name){
			*ent = (Quad*)_entities[i];
			return true;
		}
	}
	return false;
}

bool Scene::getEntity(Mesh** ent ,std::string name)
{
	if(_entities3D.empty())
		return false;

	for(int i=0; i < _entities3D.size(); i++){
		if(_entities3D[i]->name() == name){
			*ent = (Mesh*)_entities3D[i];
			return true;
		}
	}
}

void Scene::AddEntity(Entity2D* entity)
{
	_entities.push_back(entity);
}

void Scene::AddEntity(Entity3D* entity){
	_entities3D.push_back(entity);
} 

void Scene::setName(std::string sceneName)
{
	_name = sceneName;
}