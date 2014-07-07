#include "testGame.h"
#include "Input/directinput.h"
#include "Entity2D\Sprite.h"
using namespace Erio;
Game::Game()
{
}
bool Game::Init(Inaba::Renderer& renderer)
{
	currentScene().getEntity(&_sprite1, "player1");
	currentScene().getEntity(&_sprite2, "player2");
	currentScene().getEntity(&_quad1, "floor");
	return true;
}
void Game::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{
	
	 static float fSp = 1.0f;

	 

	 if(directInput.keyDown(Inaba::Input::KEY_UP)){
	  _sprite1->setPos(_sprite1->posX(), _sprite1->posY() + fSp);
	 }

	if(directInput.keyDown(Inaba::Input::KEY_DOWN)){
	  _sprite1->setPos(_sprite1->posX(), _sprite1->posY() - fSp);
	 }

	 if(directInput.keyDown(Inaba::Input::KEY_LEFT)){
	  _sprite1->setPos(_sprite1->posX() - fSp, _sprite1->posY());
	 }

	 if(directInput.keyDown(Inaba::Input::KEY_RIGHT)){
	  _sprite1->setPos(_sprite1->posX() + fSp, _sprite1->posY());
	 }

	if(_sprite1->checkCollision(*_quad1) != Inaba::Entity2D::NoCollision ){
		_sprite1->returnToPos(_sprite1->prevPosX(), _sprite1->prevPosY());
	}

	/*static float rot = 0.0f;
	rot += 0.001f;
	_quad1.setRotation(rot);

	_quad1.Draw(renderer);
	_quad1.drawAABB(renderer);

	//_ent1->Draw(renderer);
	//_ent1->drawAABB(renderer);

	_quad2.Draw(renderer);

	_sprite1.setAnimation(&_anim1);
	_sprite1.Update(timer);
	_sprite1.Draw(renderer);
	_sprite1.drawAABB(renderer);
	*/
	 _sprite1->Update(timer);
	 _sprite2->Update(timer);
}
void Game::DeInit()
{
}