#include "Node.h"
#include "../Renderer/Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Node::Node()
{

}

Node::Node(Node* parent)
{
	parent = _parent;
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
	Entity3D::UpdateTransformation();
	for(list<Entity3D*>::iterator iter = childs.begin(); iter != childs.end(); iter++)
	{
		(*iter)->UpdateTransformation();
	}
}

void Mesh::Draw(Renderer& renderer) const{
	_vertexBuffer3D->bind();
	_indexBuffer->bind();
	renderer.setCurrentTexture(NoTexture);
	renderer.setMatrix(World,_transformationMatrix);
	renderer.Draw(pPrimitive);
}