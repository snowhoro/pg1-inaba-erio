#ifndef NODE_H
#define NODE_H

#include "Entity3D.h"
#include "Mesh.h"
#include <list>
#include "../myengine_api.h"
using namespace std;

namespace Inaba
{	
	class Entity3D;
	class MYENGINE_API Node : public Entity3D
	{
		public:
			Node();
			Node(Node*);
			~Node();

			void AddChild(Entity3D*);
			void RemoveChild(Entity3D*);
            void Draw(Renderer& r) const;
			void UpdateTransformation();
		private:
			
			list<Entity3D*> childs;
	};
}
#endif