#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D.h"
#include "../Renderer/xMath.h"
#include "../Renderer/RenderTypes.h"
#include "../myengine_api.h"

namespace Inaba
{
	class Renderer;
	class Animation;
	class Timer;

	class MYENGINE_API Sprite : public Entity2D
	{
		public:
			Sprite();
			~Sprite();

			void setTexture(Texture&);
			void setTextureCoords  (float fU1, float fV1,
									float fU2, float fV2,
									float fU3, float fV3,
									float fU4, float fV4
								   );

			void Draw(Renderer&) const;
			void setAnimation(Animation*);
			void Update(Timer&);

		private:
			Texture _texture;
			TextureCoordVertex* _vertex;
			Animation *_animation;
			unsigned int _previousFrame;
	};
}

#endif