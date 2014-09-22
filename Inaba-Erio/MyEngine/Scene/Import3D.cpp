#include "Import3D.h"
#include "Scene.h"
#include <string>
#include "../Entity3D/Entity3D.h"
#include "../Entity3D/Mesh.h"
#include "../Renderer/Renderer.h"

using namespace Inaba;

Import3D* Import3D::_instance = NULL;

Import3D::Import3D()
: _renderer(NULL)
{
}

Import3D* Import3D::GetInstance()
{
	if (!_instance)
	{
		_instance = new Import3D();
	}
	return _instance;
}

void Import3D::setRenderer(Renderer *renderer)
{
	_renderer = renderer;
}

bool Import3D::importScene(const std::string& fileName,Scene& scene)
{
	std::ifstream fin(fileName.c_str());
	if(fin.fail()){
		fin.close();
	}

	  Assimp::Importer meshImporter;
		const aiScene* objScene = meshImporter.ReadFile( fileName, 
													  aiProcess_CalcTangentSpace       | 
													  aiProcess_Triangulate            |
													  aiProcess_JoinIdenticalVertices  |
													  aiProcess_SortByPType);

  if( !objScene)
  {
	  //mandar mensajes de window
    return false;
  }

  if(objScene->mMeshes[0])
  {
	aiMesh** myAiMeshes = &objScene->mMeshes[0];

    UINT numVertices = 0;
    UINT numFaces = 0;
    UINT inx_vertex = 0;
    UINT inx_faces = 0;
    UINT startIndex = 0;
	ColorVertex* vertices;
	USHORT* indices;

	Inaba::Mesh* myMesh = new Inaba::Mesh(*_renderer);
	
	for(int nMeshes = 0; nMeshes < objScene->mNumMeshes; nMeshes++)
    {
		numVertices += myAiMeshes[nMeshes]->mNumVertices;
	    numFaces += myAiMeshes[nMeshes]->mNumFaces;
	}

	vertices = new ColorVertex[numVertices];

	for(int nMeshes = 0; nMeshes < objScene->mNumMeshes; nMeshes++)
	{
	    startIndex = inx_vertex;
		for(int nVertex = 0; nVertex < myAiMeshes[nMeshes]->mNumVertices; nVertex++)
		{
			vertices[inx_vertex].x = myAiMeshes[nMeshes]->mVertices[nVertex].x;
			vertices[inx_vertex].y = myAiMeshes[nMeshes]->mVertices[nVertex].y;
			vertices[inx_vertex].z = myAiMeshes[nMeshes]->mVertices[nVertex].z;
			//vertices[inx_vertex].Nx = myAiMeshes[nMeshes]->mNormals[nVertex].x;
			//vertices[inx_vertex].Ny = myAiMeshes[nMeshes]->mNormals[nVertex].y;
			//vertices[inx_vertex].Nz = myAiMeshes[nMeshes]->mNormals[nVertex].z;
			vertices[inx_vertex].color = D3DCOLOR_XRGB(255,255,255);
			inx_vertex++;
		}
		for(int nFaces = 0; nFaces < myAiMeshes[nMeshes]->mNumFaces; nFaces++)
		{
			indices[inx_faces++] = myAiMeshes[nMeshes]->mFaces[nFaces].mIndices[0] + startIndex;
			indices[inx_faces++] = myAiMeshes[nMeshes]->mFaces[nFaces].mIndices[1] + startIndex;
			indices[inx_faces++] = myAiMeshes[nMeshes]->mFaces[nFaces].mIndices[2] + startIndex;
		}
		
		myMesh->setData(vertices, myAiMeshes[nMeshes]->mNumVertices,Inaba::TriangleList,indices,numVertices);
		myMesh->setScale(100,100,100);
		myMesh->setPos(100,100,0);


	}
	
  }

}


