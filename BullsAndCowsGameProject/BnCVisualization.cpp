#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

int searchedNum[4] = {0, 0, 0, 0};
int PlayersGuess[4]	= {0, 0, 0, 0};

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;

SDL_Texture* gKeyPressTextures[10];
SDL_Texture* gDigitsTexture[4];

SDL_Texture* gCurrentTexture = NULL;
SDL_Texture* gBullTexture = NULL;
SDL_Texture* gCowTexture = NULL;
SDL_Texture* gBullsTexture[4];
SDL_Texture* gCowsTexture[4];
SDL_Texture* gWinTexture = NULL;
SDL_Texture* gBadNumber = NULL;

SDL_Renderer* gRenderer = NULL;


bool init() {
		bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", 400, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf("Window could not be created %s", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				printf("renderer failed %s", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n",	IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


SDL_Texture* loadTexture( string path )
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if(newTexture == NULL)
		{
			printf(" unable to create texture %s\n ", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}


bool loadMedia()
{
	bool success = true;

	gKeyPressTextures[0] = loadTexture("images/1.png");
	gKeyPressTextures[1] = loadTexture("images/2.png");
	gKeyPressTextures[2] = loadTexture("images/3.png");
	gKeyPressTextures[3] = loadTexture("images/4.png");
	gKeyPressTextures[4] = loadTexture("images/5.png");
	gKeyPressTextures[5] = loadTexture("images/6.png");
	gKeyPressTextures[6] = loadTexture("images/7.png");
	gKeyPressTextures[7] = loadTexture("images/8.png");
	gKeyPressTextures[8] = loadTexture("images/9.png");
	gKeyPressTextures[9] = loadTexture("images/default.png");

	gBullTexture= loadTexture("images/bull.png");
	gCowTexture = loadTexture("images/cow.png");

	gWinTexture = loadTexture("images/win.png");
	gBadNumber = loadTexture("images/badnumber.png");
	return success;
}

void close() {
	SDL_DestroyTexture(gCurrentTexture);
	gCurrentTexture = NULL;

	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

}

void generate() {
		int i = 0;
		bool NO = false;
		while(i < 4) {		
			int randInd = 1 + (rand() % (10 - 1 + 1));
			for (int j = 0; j < 4; j++) {
				if(randInd == searchedNum[j] && j !=  i) {
					NO = true;
				}
			}

			if( NO == false) {
				searchedNum[i] = randInd;
				i++;
			}	
		}
	}

	bool ifCorrectNum() {
		bool CorrectNum = true;

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				if(PlayersGuess[i] == PlayersGuess[j] && i != j)
					CorrectNum = false;
			}
		}
		return CorrectNum;		
	}

	void bullsAndCowsCount(int bulls, int cows) {
		for(int i = 0; i < bulls; i++) {
			gBullsTexture[i] = gBullTexture;
		}

		for(int i = 0; i < cows; i++) {
			gCowsTexture[i] = gCowTexture;
		}
	}

	SDL_Rect BaC[8];
		void BullsAndCowsVP() {

			for(int i= 0; i < 8; i++) {
						BaC[i].x = (SCREEN_WIDTH / 8) * i;
						BaC[i].y = SCREEN_HEIGHT/2;
						BaC[i].w = SCREEN_WIDTH/8;
						BaC[i].h = SCREEN_HEIGHT/2;
						SDL_Rect current = BaC[i];
						SDL_RenderSetViewport(gRenderer, &current);
						if( i < 4) {
							SDL_RenderCopy(gRenderer, gBullsTexture[i], NULL, NULL);
						}
						else
						{
							SDL_RenderCopy(gRenderer, gCowsTexture[i-4], NULL, NULL);
						}


			}
				SDL_RenderPresent(gRenderer);
				for(int i = 0; i < 8; i++) {
					if(i < 4) {
						gBullsTexture[i] = NULL;
					}
					else {
						gCowsTexture[i-4] = NULL;
					}
				}
		}

int main(int argc, char* argv[]) {

	int	cows = 0,
		bulls = 0,
		none = 0;
	int n=0;
		bool defPressed = false, notCorrectNum = false;

	generate();

	init();
	loadMedia();

	bool quit = false;

	SDL_Event e;

	while(!quit) {

		while(SDL_PollEvent (&e) != 0)
			{

				if(e.type == SDL_QUIT) {
					quit = true;
				}
				else if(e.type == SDL_KEYDOWN)
				{
						switch(e.key.keysym.sym)
						{
						case SDLK_1:
							PlayersGuess[n] = 1;
							n++;
							break;

						case SDLK_2:
							PlayersGuess[n] = 2;
							n++;
							break;

						case SDLK_3:
							PlayersGuess[n] = 3;
							n++;
							break;

						case SDLK_4:
							PlayersGuess[n] = 4;
							n++;
							break;

						case SDLK_5:
							PlayersGuess[n] = 5;
							n++;
							break;

						case SDLK_6:
							PlayersGuess[n] = 6;
							n++;
							break;

						case SDLK_7:
							PlayersGuess[n] = 7;
							n++;
							break;

						case SDLK_8:
							PlayersGuess[n] = 8;
							n++;
							break;

						case SDLK_9:	
							PlayersGuess[n] = 9;
							n++;			
							break;

						case SDLK_SPACE: 
							cout << "SPACE " << endl;
							if(n != 4) {
								for(int i = 0; i < 4; i++) {
									gDigitsTexture[i] = gBadNumber;
								}
								cout << "too malko or golqmo number \n";
								n = 0;
							}
							else
							{
								if( ifCorrectNum() == false) {
									cout << "povtarq see \n";
									n = 0;
								}
								else
								{

									bulls = 0;
									cows = 0;
									n = 0;
									cout << "NULIRA " << n << endl;



									for(int i = 0; i < 4; i++) {
										for(int g = 0; g < 4; g++) {
											if(searchedNum[i] == PlayersGuess[g]) {
												if( i == g ) {
													bulls += 1;
												}
												else {
													cows += 1;
												}
											}
											else {
												none += 1;
											}
										}
									}

									cout << cows << " Cows " << endl << bulls << " Bulls " << endl; 

									bullsAndCowsCount(bulls, cows);


								//	for(int i = 0; i < 4; i++) {
								//		cout << PlayersGuess[i];
								//	}

								}	

							}

						break;

						default:
							defPressed = true;
							for(int i = 0; i < 4; i++) {
								gDigitsTexture[i] = gKeyPressTextures[9] ;
							}	
						break;
					}


						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						SDL_RenderPresent(gRenderer);

					//	cout << n << endl;
						if(n > 4) 
							n = 0;


						for(int i = 0; i < 4; i++) {
								int index = PlayersGuess[i];
								gDigitsTexture[i] = gKeyPressTextures[index-1];
						}

						if(bulls == 4) {
							for(int i = 0; i < 4; i++) {
								gDigitsTexture[i] = gWinTexture ;
							}
						}

							//filling bulls and cows's viewports
							BullsAndCowsVP();


								SDL_Rect firstDigit;
								firstDigit.x = 0;
				 				firstDigit.y = 0;
								firstDigit.w = SCREEN_WIDTH/4;
								firstDigit.h = SCREEN_HEIGHT/2;
								SDL_RenderSetViewport(gRenderer, &firstDigit);
								SDL_RenderCopy(gRenderer, gDigitsTexture[0], NULL, NULL);

								SDL_Rect secDigit;
								secDigit.x = SCREEN_WIDTH/4;
								secDigit.y = 0;
								secDigit.w = SCREEN_WIDTH/4;
								secDigit.h = SCREEN_HEIGHT/2;
								SDL_RenderSetViewport(gRenderer, &secDigit);
								SDL_RenderCopy(gRenderer, gDigitsTexture[1], NULL, NULL);

								SDL_Rect thirdDigit;
								thirdDigit.x = SCREEN_WIDTH/2;
								thirdDigit.y = 0;
								thirdDigit.w = SCREEN_WIDTH/4;
								thirdDigit.h = SCREEN_HEIGHT/2;
								SDL_RenderSetViewport(gRenderer, &thirdDigit);
								SDL_RenderCopy(gRenderer, gDigitsTexture[2], NULL, NULL);

								SDL_Rect fourthDigit;
								fourthDigit.x = (SCREEN_WIDTH/4)*3;
								fourthDigit.y = 0;
								fourthDigit.w = SCREEN_WIDTH/4;
								fourthDigit.h = SCREEN_HEIGHT/2;
								SDL_RenderSetViewport(gRenderer, &fourthDigit);
								SDL_RenderCopy(gRenderer, gDigitsTexture[3], NULL, NULL);

								SDL_RenderPresent(gRenderer);
						}
				}
			 }
	return 0;
}
