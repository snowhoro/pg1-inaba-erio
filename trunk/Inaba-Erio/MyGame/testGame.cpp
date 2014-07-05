#include "testGame.h"
#include "directinput.h"

using namespace Erio;

Game::Game()
{
}
bool Game::Init(Inaba::Renderer& renderer)
{
	_quad1.setScale(100.0f,100.0f);
	_quad1.setPos(100.0f, 100.0f);

	_quad2.setScale(200.0f,200.0f);
	_quad2.setPos(-100.0f, -100.0f);
	_quad2.setRotation(-45.0f);

	_sprite1.setScale(300.0f,300.0f);
	_sprite1.setPos(0.0f,0.0f);

	Inaba::Texture texture = renderer.LoadTexture("logo.png",D3DCOLOR_XRGB(0,0,0));
	_sprite1.setTexture(texture);

	return true;
}
void Game::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{
	 static float fSp = 1.0f;

	 if(directInput.keyDown(Inaba::Input::KEY_UP)){
	  _sprite1.setPos(_sprite1.posX(), _sprite1.posY() + fSp);
	 }

	 if(directInput.keyDown(Inaba::Input::KEY_DOWN)){
	  _sprite1.setPos(_sprite1.posX(), _sprite1.posY() - fSp);
	 }

	 if(directInput.keyDown(Inaba::Input::KEY_LEFT)){
	  _sprite1.setPos(_sprite1.posX() - fSp, _sprite1.posY());
	 }

	 if(directInput.keyDown(Inaba::Input::KEY_RIGHT)){
	  _sprite1.setPos(_sprite1.posX() + fSp, _sprite1.posY());
	 }

	static float rot = 0.0f;
	rot += 0.001f;
	_quad1.setRotation(rot);

	_quad1.Draw(renderer);
	_quad2.Draw(renderer);

	_sprite1.Draw(renderer);

}
void Game::DeInit()
{
}