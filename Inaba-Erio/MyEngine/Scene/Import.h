#ifndef IMPORT_H
#define IMPORT_H

#include "../myengine_api.h"
#include <string>
#include "../xml/tinyxml2.h"
#include <list>
namespace Inaba
{
	
	class Scene;
	class Quad;
	class Sprite;
	class Animation;
	class Renderer;

	class MYENGINE_API Import
	{
		public:
			static bool importScene(Scene&, std::string, Renderer*);
			static void importSprite(Scene&,tinyxml2::XMLElement*,Renderer*);
			static void importQuad(Scene&,tinyxml2::XMLElement*);
			static void importAnimation(std::list<Animation> *animations,tinyxml2::XMLElement*);
	};
}


#endif
