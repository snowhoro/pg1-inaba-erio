#ifndef MESH_H
#define MESH_H

#include "Entity3D.h"
#include "../Renderer/xMath.h"
#include "../Renderer/RenderTypes.h"
#include "../VertexBuffer/indexbuffer.h"
#include "../VertexBuffer/vertexbuffer3D.h"
#include "../myengine_api.h"

namespace Inaba
{
	class Renderer;
	class Timer;
	
	class MYENGINE_API Mesh : public Entity3D
	{
		public:
			Mesh(Renderer & p_Renderer);
			~Mesh();

			void setData(size_t vertexCount, Inaba::Primitive, const unsigned short*, size_t indexCount);
            void Draw(Renderer& r) const;
			void Update(Timer&);
		private:
			ColorVertex* _vertex;
			IndexBuffer* _indexBuffer;
			VertexBuffer3D* _vertexBuffer3D;
			Primitive pPrimitive;
			Renderer& _renderer;
	};
}
#endif