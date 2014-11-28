#include "Import3D.h"
#include "Scene.h"
#include <string>
#include "../Entity3D/Entity3D.h"
#include "../Entity3D/Mesh.h"
#include "../Entity3D/Node.h"
#include "../Renderer/Renderer.h"
#include <math.h>

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
	UINT inx_faces = 0;

	TextureCoordVertex* vertices;
	USHORT* indices;

	

	numVertices += myAiMeshes->mNumVertices;
	numFaces += myAiMeshes->mNumFaces;
	vertices = new TextureCoordVertex[numVertices];
	indices = new USHORT[numFaces*3];


	for(int nVertex = 0; nVertex < myAiMeshes->mNumVertices; nVertex++)
	{
		vertices[nVertex].x = myAiMeshes->mVertices[nVertex].x;
		vertices[nVertex].y = myAiMeshes->mVertices[nVertex].y;
		vertices[nVertex].z = myAiMeshes->mVertices[nVertex].z;
		//vertices[inx_vertex].Nx = myAiMeshes[nMeshes]->mNormals[nVertex].x;
		//vertices[inx_vertex].Ny = myAiMeshes[nMeshes]->mNormals[nVertex].y;
		//vertices[inx_vertex].Nz = myAiMeshes[nMeshes]->mNormals[nVertex].z;
	}

	for(int nFaces = 0; nFaces < myAiMeshes->mNumFaces; nFaces++)
	{
		indices[inx_faces++] = myAiMeshes->mFaces[nFaces].mIndices[0];
		indices[inx_faces++] = myAiMeshes->mFaces[nFaces].mIndices[1];
		indices[inx_faces++] = myAiMeshes->mFaces[nFaces].mIndices[2];
	}

	Mesh *myMesh = new Mesh(*_renderer);
	myMesh->setData(vertices, myAiMeshes->mNumVertices,Inaba::TriangleList,indices,numFaces*3);
	myMesh->setPos(0,0,0);
	
	scene.AddEntity(myMesh);

	delete vertices;
	delete indices;

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

	Node* myNode = importNode(objScene->mRootNode, objScene, scene);
	//scene.AddEntity(myNode);

	return true;
}

Node* Import3D::importNode(aiNode* myAiNode,const aiScene* myAiScene, Scene& scene)
{	

	Node *myNode = new Node();

	for(int nChild=0; nChild < myAiNode->mNumChildren; nChild++)
	{
		Node *myChildren = importNode(myAiNode->mChildren[nChild], myAiScene , scene);		
		myChildren->SetParent(myNode);
		myNode->AddChild(myChildren);

		aiVector3t<float> scaling;
		aiQuaterniont<float> rotation;
		aiVector3t<float> position;
		myAiNode->mTransformation.Decompose(scaling,rotation,position);
		myNode->setPos(position.x,position.y,position.z);
		myNode->setScale(scaling.x,scaling.y,scaling.z);
		float rotX, rotY, rotZ;
		quaternionToEuler(rotation.x,rotation.y,rotation.z,rotation.w,rotX,rotY,rotZ);
		myNode->setRotation(rotX,rotY,rotZ);

	}

	
	for(int nMeshes=0; nMeshes < myAiNode->mNumMeshes ; nMeshes++)
	{
		importMesh(myAiScene->mMeshes[myAiNode->mMeshes[nMeshes]], scene);
	}
	
	scene.AddEntity(myNode);
	return myNode;

}

void Import3D::quaternionToEuler(float qX,float qY,float qZ,float qW,float& rotX,float& rotY,float& rotZ)
{
	double test = qX * qY + qZ * qW;
	if(test > 0.499)
	{
		rotX = 2.0 * atan2(qX,qW);
		rotY = AI_MATH_PI_F / 2;
		rotZ = 0;
		return;
	}
	if(test < -0.499)
	{
		rotX = - 2.0 * atan2(qX,qW);
		rotY = - AI_MATH_PI_F / 2;
		rotZ = 0;
		return;
	}
	float sqx = qX*qX;
    float sqy = qY*qY;
    float sqz = qZ*qZ;

	rotX = atan2(2*qY*qW-2*qX*qZ , 1 - 2*sqy - 2*sqz);
	rotY = asin(2*test);
	rotZ = atan2(2*qX*qW-2*qY*qZ , 1 - 2*sqx - 2*sqz);
}
