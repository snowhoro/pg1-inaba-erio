#ifndef IMPORT3D_H
#define IMPORT3D_H

#include "../myengine_api.h"
#include <string>
#include <fstream>
#include "../Assimp32/include/Importer.hpp"
#include "../Assimp32/include/scene.h"
#include "../Assimp32/include/postprocess.h"

namespace Inaba
{	
	class Scene;
	class Mesh;
	class Renderer;
	class Node;

	class MYENGINE_API Import3D
	{
		private:
			static Import3D *_instance;
			Renderer *_renderer;
			Import3D();
			Import3D(Import3D &const);
			Import3D& operator= (Import3D const&);

		public:
			static Import3D* GetInstance();
			void setRenderer(Renderer*);
			bool importMesh(aiMesh*,Scene&);
			Node* importNode(aiNode*,const aiScene*,Scene&);
			bool importScene(const std::string&,Scene&);
	};
}
#endif
