#include "Sprite.h"
#include "Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Sprite::Sprite():
Entity2D(),
_texture(NoTexture),
_vertex(new TextureCoordVertex[4])
{
	static const float SIZE = 0.5f;
	_vertex[0].x = -SIZE;	_vertex[0].y = SIZE;	_vertex[0].z = 0.0f;
	_vertex[1].x = SIZE;	_vertex[1].y = SIZE;	_vertex[1].z = 0.0f;
	_vertex[2].x = -SIZE;	_vertex[2].y = -SIZE;	_vertex[2].z = 0.0f;
	_vertex[3].x = SIZE;	_vertex[3].y = -SIZE;	_vertex[3].z = 0.0f;

	_vertex[0].u = 0.0;		_vertex[0].v = 0.0;
	_vertex[1].u = 1.0;		_vertex[1].v = 0.0;
	_vertex[2].u = 0.0;		_vertex[2].v = 1.0;
	_vertex[3].u = 1.0;		_vertex[3].v = 1.0;

	//UpdateLocalTransformation();
}

Sprite::~Sprite()
{
	delete[] _vertex;
	_vertex = NULL;
}

void Sprite::setTexture(Texture& texture)
{
	_texture = texture;
}

void Sprite::setTextureCoords  (float fU1, float fV1,
								float fU2, float fV2,
								float fU3, float fV3,
								float fU4, float fV4)
{
	_vertex[0].u = fU1;		_vertex[0].v = fV1;
	_vertex[1].u = fU2;		_vertex[1].v = fV2;
	_vertex[2].u = fU3;		_vertex[2].v = fV3;
	_vertex[3].u = fU4;		_vertex[3].v = fV4;
}

void Sprite::Draw(Renderer& renderer) const
{
	renderer.setCurrentTexture(_texture);
	renderer.setMatrix(World,_transformationMatrix);
	renderer.Draw(_vertex,Inaba::TriangleStrip, 4);
}