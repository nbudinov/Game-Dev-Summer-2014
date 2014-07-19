#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <SDL_mixer.h>
#include <sstream>


class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile( std::string path, SDL_Renderer* gRenderer = NULL );
		
		#ifdef _SDL_TTF_H 
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
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
