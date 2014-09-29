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

bool Import3D::importMesh(aiMesh* myAiMeshes,Scene& scene)
{
	UINT numVertices = 0;
	UINT numFaces = 0;
	UINT inx_vertex = 0;
	UINT inx_faces = 0;

	TextureCoordVertex* vertices;
	USHORT* indices;

	numVertices += myAiMeshes->mNumVertices;
	numFaces += myAiMeshes->mNumFaces;
	vertices = new TextureCoordVertex[numVertices];
	indices = new USHORT[numFaces];


	for(int nVertex = 0; nVertex < myAiMeshes->mNumVertices; nVertex++)
	{
		vertices[inx_vertex].x = myAiMeshes->mVertices[nVertex].x;
		vertices[inx_vertex].y = myAiMeshes->mVertices[nVertex].y;
		vertices[inx_vertex].z = myAiMeshes->mVertices[nVertex].z;
		//vertices[inx_vertex].Nx = myAiMeshes[nMeshes]->mNormals[nVertex].x;
		//vertices[inx_vertex].Ny = myAiMeshes[nMeshes]->mNormals[nVertex].y;
		//vertices[inx_vertex].Nz = myAiMeshes[nMeshes]->mNormals[nVertex].z;

		inx_vertex++;
	}
	for(int nFaces = 0; nFaces < myAiMeshes->mNumFaces; nFaces++)
	{
		indices[inx_faces] = myAiMeshes->mFaces[nFaces].mIndices[0];
		indices[inx_faces] = myAiMeshes->mFaces[nFaces].mIndices[1];
		indices[inx_faces] = myAiMeshes->mFaces[nFaces].mIndices[2];

		inx_faces++;
	}

	Mesh *myMesh = new Mesh(*_renderer);
	myMesh->setData(vertices, myAiMeshes->mNumVertices,Inaba::TriangleList,indices,numVertices);
	myMesh->setPos(100,100,0);
	scene.AddEntity(myMesh);

	return true;
}

bool Import3D::importScene(const std::string& fileName,Scene& scene)
{
	Assimp::Importer meshImporter;
	const aiScene* objScene = meshImporter.ReadFile( fileName.c_str(), 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals | 
		aiProcess_FlipUVs);

	if( !objScene)
	{
		//mandar mensajes de window
		return false;
	}

	for(int nMeshes=0; nMeshes < objScene->mNumMeshes ; nMeshes++)
	{
		importMesh(objScene->mMeshes[nMeshes], scene);
	}
}





