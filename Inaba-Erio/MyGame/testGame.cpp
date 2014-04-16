#include "testGame.h"
#include "Renderer.h"

using namespace Erio;

Game::Game()
{
}
bool Game::Init(Inaba::Renderer& renderer)
{
	static const float SIZE = 0.5f;

	_vertex[0].x = -SIZE;	_vertex[0].y = SIZE;	_vertex[0].z = 0.0f;
	_vertex[1].x = SIZE;	_vertex[1].y = SIZE;	_vertex[1].z = 0.0f;
	_vertex[2].x = -SIZE;	_vertex[2].y = -SIZE;	_vertex[2].z = 0.0f;
	_vertex[3].x = SIZE;	_vertex[3].y = -SIZE;	_vertex[3].z = 0.0f;

	_vertex[0].color = D3DCOLOR_XRGB(0,0,0);	
	_vertex[1].color = D3DCOLOR_XRGB(0,0,0);	
	_vertex[2].color = D3DCOLOR_XRGB(0,0,0);	
	_vertex[3].color = D3DCOLOR_XRGB(0,0,0);	

	return true;
}
void Game::Frame(Inaba::Renderer& renderer)
{
	renderer.Draw(_vertex,Inaba::TriangleStrip,4);
}
void Game::DeInit()
{
}