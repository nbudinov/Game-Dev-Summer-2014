#include "LMenu.h"


LMenu::LMenu(SDL_Renderer* gRenderer)
{
	font = NULL;

	SDL_Color textColor = { 0xff, 0x65, 0xdc };
	SDL_Color pacColor = { 0xff, 0xec, 0x00 }; 
	LMenu::setFont();

	bgTex.loadFromFile("Data/Art/intro.jpg", gRenderer);
	pacman.loadFromRenderedText( "PACMAN!", pacColor, gRenderer, font); 
	start.loadFromRenderedText( "START", textColor, gRenderer, font); 
	exit.loadFromRenderedText( "EXIT", textColor, gRenderer, font); 

	arrow.loadFromFile("Data/Art/Arrow.png", gRenderer);
	
	SDL_Rect rstart = {200, 350, 250, 80};
	SDL_Rect rexit = {200, 450, 200, 80};
	SDL_Rect arrow = {260, 250, 40, 45};

	LMenu::startRect = rstart;
	LMenu::exitRect = rexit;
	LMenu::arrowRect = arrow;

	LMenu::arrowRect.x = startRect.x - arrowRect.w - 5;

	LMenu::gRenderer = gRenderer;

	choice = 2;
}


LMenu::~LMenu(void)
{
}

void LMenu::run()
{
	bool quit = false;

	SDL_Event e;

	while( !quit )
	{
		while( SDL_PollEvent(&e) != 0 )
		{
			switch( e.key.keysym.sym )
			{
				case SDLK_RETURN:
					quit = true;
					break;
			}

			update(e);

		}

		render();
	}

}

void LMenu::update(SDL_Event e)
{
    if( e.type == SDL_KEYDOWN )
    { 
         switch( e.key.keysym.sym )
         {
			case SDLK_UP:
				choice ++;
				break;
			case SDLK_DOWN:
				choice --;
				break;
			default:
				break;
         }
    }

	if(choice > 2)
		choice = 1;
	if(choice < 1)
		choice = 2;

	if(choice == 2)
		LMenu::arrowRect.y = startRect.y + startRect.h / 2 - arrowRect.h / 2;
	else
		LMenu::arrowRect.y = exitRect.y + exitRect.h / 2 - arrowRect.h / 2;

	printf("%d\n", choice);



}

void LMenu::render()
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			SDL_RenderClear( gRenderer );

	pacman.render(100, 0, gRenderer, SDL_FLIP_NONE, 350, 150);
	bgTex.render(0, 0, gRenderer, SDL_FLIP_NONE, SCREEN_WIDTH, SCREEN_HEIGHT - 150);
	start.render(startRect.x, startRect.y, gRenderer, SDL_FLIP_NONE, startRect.w, startRect.h);
	exit.render(exitRect.x, exitRect.y, gRenderer, SDL_FLIP_NONE, exitRect.w, exitRect.h);
	arrow.render(arrowRect.x, arrowRect.y, gRenderer, SDL_FLIP_NONE, arrowRect.w, arrowRect.h);

	SDL_RenderPresent( gRenderer );
}

bool LMenu::setFont()
{
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

	font = TTF_OpenFont( "Data/Fonts/pacmania.ttf", 420 );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
}

int LMenu::isFinished()
{
	return choice;
}
