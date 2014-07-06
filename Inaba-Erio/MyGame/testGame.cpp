#include "testGame.h"
#include "Input/directinput.h"

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

	_sprite1.setScale(100.0f,100.0f);
	_sprite1.setPos(0.0f,0.0f);

	Inaba::Texture texture = renderer.LoadTexture("Link.png",Inaba_COLOR_RGB(0,255,0));
	_sprite1.setTexture(texture);
	_anim1.setLength(1500.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 94.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 144.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 194.0f, 20.0f, 23.0f, 41.0f);
	_anim1.addFrame(512.0f,1024.0f, 144.0f, 20.0f, 23.0f, 41.0f);


	_sprite1.setAnimation(&_anim1);

	_ent1 = &_quad1;


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

	 if(_sprite1.checkCollision(_quad1) != Inaba::Entity2D::NoCollision ){
		_sprite1.returnToPos(_sprite1.prevPosX(), _sprite1.prevPosY());
	}

	static float rot = 0.0f;
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

}
void Game::DeInit()
{
}