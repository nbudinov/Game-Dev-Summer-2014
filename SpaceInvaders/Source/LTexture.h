

//#ifndef _LTEXTURE
//#define _LTEXTURE

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream>

class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile( std::string path, SDL_Renderer* gRenderer = NULL );
		
		#ifdef _SDL_TTF_H 
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont );
		#endif

		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );
		
		void render( int x, int y, SDL_Renderer* gRenderer);

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
		
		int mWidth;
		int mHeight;
};

//#endif  /* _LTEXTURE */