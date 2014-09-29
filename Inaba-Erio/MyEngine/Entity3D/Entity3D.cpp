#define NOMINMAX

#include "Entity3D.h"
#include "../Renderer/Renderer.h"
#include <Windows.h>
#include <iostream>
#include <d3dx9.h>

using namespace Inaba;

Entity3D::Entity3D():
_posX(0.0f),
_posY(0.0f),
_posZ(0.0f),
_prevPosX(0.0f),
_prevPosY(0.0f),
_prevPosZ(0.0f),
_rotation(0.0f),
_scaleX(1.0f),
_scaleY(1.0f),
_scaleZ(1.0f),
_transformationMatrix(new D3DXMATRIX())
{
}

Entity3D::~Entity3D()
{
	delete _transformationMatrix;
	_transformationMatrix = NULL;
}

void Entity3D::setPos(float posX, float posY, float posZ)
{
	_prevPosX = _posX;
	_prevPosY = _posY;
	_prevPosZ = _posZ;
	_posX = posX;
	_posY = posY;
	_posZ = posZ;

	UpdateLocalTransformation();
}

void Entity3D::setRotation(float rotation)
{
	_rotation = rotation;

	UpdateLocalTransformation();
}

void Entity3D::setScale(float scaleX, float scaleY, float scaleZ)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;

	UpdateLocalTransformation();
}

void Entity3D::UpdateLocalTransformation()
{
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, _posX, _posY, _posZ);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, _rotation);

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&translateMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&rotationMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&scaleMatrix,_transformationMatrix);

}

float Entity3D::posX() const
{
	return _posX;
}

float Entity3D::posY() const
{
	return _posY;
}

float Entity3D::posZ() const
{
	return _posZ;
}

float Entity3D::prevPosX() const
{
	return _prevPosX;
}

float Entity3D::prevPosY() const
{
	return _prevPosY;
}

float Entity3D::prevPosZ() const
{
	return _prevPosZ;
}

float Entity3D::scaleX() const
{
	return _scaleX;
}

float Entity3D::scaleY() const
{
	return _scaleY;
}

float Entity3D::scaleZ() const
{
	return _scaleZ;
}

Entity3D::CollisionResult Entity3D::checkCollision(Entity3D& rkEntity3D) const
{
 float fOverlapX = std::max(0.0f, 
        std::min( posX() + fabs( scaleX() ) / 2.0f,rkEntity3D.posX() + fabs( rkEntity3D.scaleX() ) / 2.0f) -  
        std::max( posX() - fabs( scaleX() ) / 2.0f,rkEntity3D.posX() - fabs( rkEntity3D.scaleX() ) / 2.0f)
 );
 float fOverlapY = std::max(0.0f, 
        std::min( posY() + fabs( scaleY() ) / 2.0f,  rkEntity3D.posY() + fabs( rkEntity3D.scaleY() ) / 2.0f) -  
        std::max( posY() - fabs( scaleY() ) / 2.0f, rkEntity3D.posY() - fabs( rkEntity3D.scaleY() ) / 2.0f)
 );

 // COLLISION Z LO HACEMOS OTRO DIA


 if(fOverlapX != 0.0f && fOverlapY != 0.0f){
  if(fOverlapX > fOverlapY){
   return CollisionVertical;
  }else{
   return CollisionHorizontal;
  }
 }

 return NoCollision;
}

/*void Entity3D::drawAABB(Renderer& rkRenderer) const
{
 static ColorVertex s_akAABBVertices[5];
 static bool s_bIsInitialized = false;
 if(!s_bIsInitialized){
  s_bIsInitialized = true;

  s_akAABBVertices[0].x = -0.5; s_akAABBVertices[0].y = -0.5; s_akAABBVertices[0].z = 0.5; s_akAABBVertices[0].color =Inaba_COLOR_RGB(255,50,50);
  s_akAABBVertices[1].x = -0.5; s_akAABBVertices[1].y = 0.5; s_akAABBVertices[1].z = 0.5; s_akAABBVertices[1].color = Inaba_COLOR_RGB(255,70,70);
  s_akAABBVertices[2].x = 0.5; s_akAABBVertices[2].y = 0.5; s_akAABBVertices[2].z = 0.5; s_akAABBVertices[2].color = Inaba_COLOR_RGB(255,30,30);
  s_akAABBVertices[3].x = 0.5; s_akAABBVertices[3].y = -0.5; s_akAABBVertices[3].z = 0.5; s_akAABBVertices[3].color = Inaba_COLOR_RGB(255,15,15);
  s_akAABBVertices[4].x = -0.5; s_akAABBVertices[4].y = -0.5; s_akAABBVertices[4].z = 0.5; s_akAABBVertices[4].color = Inaba_COLOR_RGB(255,95,90);
  s_akAABBVertices[5].x = -0.5; s_akAABBVertices[5].y = -0.5; s_akAABBVertices[5].z = -0.5; s_akAABBVertices[5].color =Inaba_COLOR_RGB(255,50,50);
  s_akAABBVertices[6].x = -0.5; s_akAABBVertices[6].y = 0.5; s_akAABBVertices[6].z = -0.5; s_akAABBVertices[6].color = Inaba_COLOR_RGB(255,70,70);
  s_akAABBVertices[7].x = 0.5; s_akAABBVertices[7].y = 0.5; s_akAABBVertices[7].z = -0.5; s_akAABBVertices[7].color = Inaba_COLOR_RGB(255,30,30);
  s_akAABBVertices[8].x = 0.5; s_akAABBVertices[8].y = -0.5; s_akAABBVertices[8].z = -0.5; s_akAABBVertices[8].color = Inaba_COLOR_RGB(255,15,15);
  s_akAABBVertices[9].x = -0.5; s_akAABBVertices[9].y = -0.5; s_akAABBVertices[9].z = -0.5; s_akAABBVertices[9].color = Inaba_COLOR_RGB(255,95,90);  

 }
 rkRenderer.setCurrentTexture(NoTexture);
 rkRenderer.setMatrix(World, _transformationMatrix );
 rkRenderer.Draw(s_akAABBVertices, Inaba::TriangleStrip, 5);
}*/

void Entity3D::returnToPos(float posX, float posY, float posZ)
{
	_posX = posX;
	_posY = posY;
	_posZ = posZ;

	UpdateLocalTransformation();
}

std::string Entity3D::name() const
{
	return _name;
}

void Entity3D::setName(std::string name)
{
	_name = name;
}