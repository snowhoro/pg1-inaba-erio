#include "Entity2D.h"
#include "Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Entity2D::Entity2D():
_posX(0.0f),
_posY(0.0f),
_rotation(0.0f),
_scale(1.0f),
_transformationMatrix(new D3DXMATRIX())
{
}

Entity2D::~Entity2D()
{
	delete _transformationMatrix;
	_transformationMatrix = NULL;
}

void Entity2D::setPos(float posX, float posY)
{
	_posX = posX;
	_posY = posY;

	UpdateLocalTransformation();
}

void Entity2D::setRotation(float rotation)
{
	_rotation = rotation;

	UpdateLocalTransformation();
}

void Entity2D::setScale(float scale)
{
	_scale = scale;

	UpdateLocalTransformation();
}

void Entity2D::UpdateLocalTransformation()
{
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, _posX, _posY, 0);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, _rotation);

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, _scale, _scale, 1);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&translateMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&rotationMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&scaleMatrix,_transformationMatrix);

}

float Entity2D::posX() const
{
	return _posX;
}

float Entity2D::posY() const
{
	return _posY;
}