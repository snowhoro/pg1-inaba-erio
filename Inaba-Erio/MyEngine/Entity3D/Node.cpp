#include "Node.h"
#include "../Renderer/Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Node::Node()
{

}

Node::Node(Node* Node)
{

}

Node::~Node()
{
	while(!childs.empty())
	{
		Entity3D* child = childs.back();
		childs.pop_back();

		delete child;
		child = NULL;
	}
}

void Node::AddChild(Entity3D* child)
{
	childs.push_back(child);
}

void Node::RemoveChild(Entity3D* child)
{
	childs.remove(child);
}

void Node::UpdateTransformation()
{
	//Entity3D::UpdateTransformation();
	
	for(list<Entity3D*>::iterator iter = childs.begin(); iter != childs.end(); iter++)
	{
		(*iter)->UpdateTransformation();
	}
}

void Node::UpdateAABB()
{
	//std::vector<Entity3D*>::iterator iter;
	for (list<Entity3D*>::iterator it = childs.begin(); it != childs.end(); it++)
	//for(list<Entity3D*>::iterator iter = childs.begin(); iter != childs.end(); iter++)
	{
		(*it)->UpdateAABB();
	}
	//UpdateAABB();
}

void Node::Update(Timer& timer)
{
	
}

void Node::Draw(Renderer& r)
{
	for (std::list<Entity3D*>::iterator it = childs.begin(); it != childs.end(); it++) {
		(*it)->Draw(r);
	}
}

list<Entity3D*> Node::getChilds(){
	return childs;
}