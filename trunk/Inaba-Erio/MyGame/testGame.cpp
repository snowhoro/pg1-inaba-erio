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
	currentScene().getEntity(&_quad2, "wall");
	return true;
}
void Game::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{	
	 static float fSp = 1.0f;
	 if(directInput.keyDown(Inaba::Input::KEY_UP))
	  _sprite1->setPos(_sprite1->posX(), _sprite1->posY() + fSp);
	 else if(directInput.keyDown(Inaba::Input::KEY_DOWN))
	  _sprite1->setPos(_sprite1->posX(), _sprite1->posY() - fSp);
	 else if(directInput.keyDown(Inaba::Input::KEY_LEFT))
	  _sprite1->setPos(_sprite1->posX() - fSp, _sprite1->posY());
	 else if(directInput.keyDown(Inaba::Input::KEY_RIGHT))
	  _sprite1->setPos(_sprite1->posX() + fSp, _sprite1->posY());
	 
	 //COLISION
	if(_sprite1->checkCollision(*_quad1) != Inaba::Entity2D::NoCollision )
		_sprite1->returnToPos(_sprite1->prevPosX(), _sprite1->prevPosY());
	if(_sprite1->checkCollision(*_quad2) != Inaba::Entity2D::NoCollision )
		_sprite1->returnToPos(_sprite1->prevPosX(), _sprite1->prevPosY());

	if(directInput.keyDown(Inaba::Input::KEY_R))
	  setScene("scene1.xml", &renderer);

}
void Game::DeInit()
{
}