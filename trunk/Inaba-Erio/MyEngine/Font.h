#ifndef FONT_H
#define FONT_H

#include "myengine_api.h"
#include "Renderer\Renderer.h"

namespace Inaba
{
	enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT }; 

	class MYENGINE_API Font
	{
		public:
			Font();
			~Font();
			bool Init( LPDIRECT3DDEVICE9 pDevice, char* faceName, int size, BOOL bold = FALSE, BOOL italic = FALSE );
			bool DeInit();
			void Print( char* text, int xPosition, int yPosition, DWORD color,
						LPD3DXSPRITE sprite = NULL,int textBoxWidth = 0, int textBoxHeight = 0, FONTALIGNMENT alignment = FA_LEFT ); 

		private:
			LPD3DXFONT _font;
	};
	 
}

#endif