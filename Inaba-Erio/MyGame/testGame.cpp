#include "testGame.h"


using namespace Erio;

Game::Game()
{
}
bool Game::Init(Inaba::Renderer& renderer)
{
	_quad1.setScale(100.0f);
	_quad1.setPos(100.0f, 100.0f);

	_quad2.setScale(200.0f);
	_quad2.setPos(-100.0f, -100.0f);
	_quad2.setRotation(-45.0f);
	return true;
}
void Game::Frame(Inaba::Renderer& renderer)
{
	static float rot = 0.0f;
	rot += 0.001f;
	_quad1.setRotation(rot);

	_quad1.Draw(renderer);
	_quad2.Draw(renderer);
}
void Game::DeInit()
{
}