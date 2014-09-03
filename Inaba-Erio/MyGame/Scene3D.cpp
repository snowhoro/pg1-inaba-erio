#include "Scene3D.h"
#include "Input/directinput.h"
#include "testGame.h"
#include <string>
#include <sstream>
#include <Entity3D\Mesh.h>

using namespace Erio;

Scene3D::Scene3D(Game *game)
{
	fileName = "scene3D.xml";
	_name = "scene3D";
	_game = game;
}

Scene3D::~Scene3D()
{

}

bool Scene3D::Init(Inaba::Renderer& renderer)
{       
  /*  _mesh1 = new Inaba::Mesh(renderer);
	_mesh1->setData(8, Inaba::Primitive::TriangleList, indices, 36);
    _mesh1->setPos(0,0,10);
    _mesh1->setScale(10,10,10);

	AddEntity(_mesh1);*/

	return true;
}

bool Scene3D::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{
	static float fSp = 1.0f;
	static float vSpd = 10.0f;
	std::string number;
	std::stringstream strstream;
	strstream << directInput.mouseRelPosX();
	strstream >> number;
	renderer.getFont()->Print((char*)("mouse X: " + number).c_str(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), NULL, 200, 0, Inaba::FA_LEFT);
	
	renderer.getCamera()->CameraControl(directInput);

	

	if(directInput.keyDown(Inaba::Input::KEY_P))
		_game->setScene("scene1", &renderer);


	return true;
}