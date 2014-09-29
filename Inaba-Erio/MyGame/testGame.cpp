#include "testGame.h"
#include "Input/directinput.h"
#include "Entity2D\Sprite.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3D.h"
using namespace Erio;

Inaba::TextureCoordVertex g_8Vertices[] = {
{-0.5f, 0.5f, -0.5f,0,0}, // 0 
{0.5f, 0.5f, -0.5f, 0,0}, // 1 
{ 0.5f, 0.5f, 0.5f, 0,0}, // 2 
{ -0.5f, 0.5f, 0.5f,0,0}, // 3

{ -0.5f, -0.5f, 0.5f, 0,0}, // 4
{  0.5f, -0.5f, 0.5f, 0,0}, // 5
{  0.5f, -0.5f,-0.5f, 0,0}, // 6
{ -0.5f, -0.5f,-0.5f, 0,0} // 7
};

USHORT g_indices[] = { 0, 1, 2, 0, 2, 3,
                                           4, 5, 6, 4, 6, 7,
                                           3, 2, 5, 3, 5, 4,
                                           2, 1, 6, 2, 6, 5,
                                           1, 7, 6, 1, 0, 7,
                                           0, 3, 4, 0, 4, 7};


Game::Game()
: Inaba::Game()
{
}

bool Game::Init(Inaba::Renderer& renderer)
{
	scene1 = new Scene1(this);
	AddScene(scene1);
	setScene("scene1", &renderer);

	scene2 = new Scene2(this);
	AddScene(scene2);

	scene3D = new Scene3D(this);
	AddScene(scene3D);

	theMesh = new Inaba::Mesh(renderer);
	theMesh->setData(g_8Vertices, 8, Inaba::TriangleList, g_indices, 36);
	theMesh->setScale(100,100,100);
	theMesh->setPos(100,100,0);


	Inaba::Import3D::GetInstance()->setRenderer(&renderer);
	Inaba::Import3D::GetInstance()->importScene("cubito.obj",*scene1);
	return true;
}

void Game::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{
	currentScene()->Frame(renderer, directInput ,timer);
	
	//theMesh->Draw(renderer);
}

void Game::DeInit(){
	delete theMesh;
	theMesh = NULL;
}