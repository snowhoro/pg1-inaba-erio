#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D.h"
#include "xMath.h"
#include "RenderTypes.h"
#include "myengine_api.h"

namespace Inaba
{
	class Renderer;

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

		private:
			Texture _texture;
			TextureCoordVertex* _vertex;
	};
}

#endif