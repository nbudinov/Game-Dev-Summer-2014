#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>

#include "ScreenConsts.h"
#include "Screen.h" 
#include "Tile.h"
#include "Player.h"
#include "LTexture.h"
#include "Game.h"
#include "LTimer.h"
#include "LMenu.h"

#undef main

Screen scr;

LTexture playerTextures[4];

LTexture scoreTex;

bool loadPlayerTex()
{
	playerTextures[0].loadFromFile( "Data/Art/player.png", scr.getRenderer() );
	playerTextures[1].loadFromFile( "Data/Art/PlayerShutHor.png", scr.getRenderer() );
	playerTextures[2].loadFromFile( "Data/Art/PlayerVert.png", scr.getRenderer() );
	playerTextures[3].loadFromFile( "Data/Art/PlayerShutVert.png", scr.getRenderer() );

	return true;
}

int main(int argc, char *argv[])
{
	Game game;

	Tile *tiles[400];

	std::vector<Tile> coins;

	scr.init();

	scr.loadMedia();

	loadPlayerTex();


	if(	scr.setTiles(tiles) == false) {
		printf("set tiles err \n");	
		return -1;
	}

	for(int i = 0; i < 400; ++i)
	{
		if(tiles[i]->getType() == 0)
			coins.push_back( Tile( tiles[i]->getBox().x, tiles[i]->getBox().y, 0 ) );
	}
	
	LTexture coinTex;
	coinTex.loadFromFile( "Data/Art/coin.png", scr.getRenderer() );
	for(int i = 0; i < coins.size(); ++i)
	{
		coins[i].tileTex = &coinTex;
	}

	bool quit = false;

	LMenu menu( scr.getRenderer() );
	menu.run();
	if(menu.isFinished() == 1)
		quit = true;

	Player player(32, 32);
	
	player.CurrentDirection = MovementRight;

	//scr.setPlayerTex(player);

	LTimer fpsTimer;
	LTimer capTimer;
	
	int countedFrames = 0;
	int anim = 0;
	fpsTimer.start();

	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

	SDL_Event e;

	while( !quit )
	{
		capTimer.start();
		while( SDL_PollEvent(&e) != 0 )
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			player.handleEvent(e);

		}


		//printf("%d, %d, %d, %d \n", leftCorn.x, leftCorn.y, leftCorn.w, leftCorn.h);

		//printf(" %d \n", player.CurrentDirection);

		player.update();

		SDL_Rect topBox = {player.getPlayerBox().x + 2, player.getPlayerBox().y - 20, 1, 20};
		SDL_Rect rightBox = {player.getPlayerBox().x + player.getPlayerBox().w, player.getPlayerBox().y + 2, 20, 1};
		SDL_Rect botBox = {player.getPlayerBox().x + 2, player.getPlayerBox().y + player.getPlayerBox().h, 1, 20};
		SDL_Rect leftBox = {player.getPlayerBox().x - 20, player.getPlayerBox().y + 2, 20, 1};
		SDL_Rect topBox2 = {player.getPlayerBox().x + player.playerBox.w - 4, player.getPlayerBox().y - 20, 1, 20};
		SDL_Rect rightBox2 = {player.getPlayerBox().x + player.playerBox.w, player.getPlayerBox().y + player.playerBox.h - 4, 20, 1};
		SDL_Rect botBox2 = {player.getPlayerBox().x + player.getPlayerBox().w - 4, player.getPlayerBox().y + player.getPlayerBox().h, 1, 20};
		SDL_Rect leftBox2 = {player.getPlayerBox().x - 20, player.getPlayerBox().y + player.playerBox.h - 4, 20, 1};

		
		if (game.Collision(player, tiles) == 1 )
		{
			player.playerBox.x += PLAYER_SPEED;

			if(player.directionY == 1)
				player.CurrentDirection = MovementUp;
			if(player.directionY == 3)
				player.CurrentDirection = MovementDown;

		}
		if (game.Collision(player, tiles) == 2 )
		{
			player.playerBox.x -= PLAYER_SPEED;
			
			if(player.directionY == 1)
				player.CurrentDirection = MovementUp;
			if(player.directionY == 3)
				player.CurrentDirection = MovementDown;
			
		}
		if (game.Collision(player, tiles) == 3 )
		{
			player.playerBox.y += PLAYER_SPEED;
			
			if(player.directionX == 2)
				player.CurrentDirection = MovementRight;
			if(player.directionX == 4)
				player.CurrentDirection = MovementLeft;
			player.directionX == 0;
			
		}
		if (game.Collision(player, tiles) == 4 )
		{
			player.playerBox.y -= PLAYER_SPEED;
			
			if(player.directionX == 2)
				player.CurrentDirection = MovementRight;
			if(player.directionX == 4)
				player.CurrentDirection = MovementLeft;
			player.directionX == 0;
			
		}
		
		for(int i = 0; i < 400; i++)
		{
			if(game.checkCollision( botBox, tiles[i]->getBox() ) && game.checkCollision( botBox2, tiles[i]->getBox() ) && player.turnDir == 3 && tiles[i]->getType() == 0 )
			{
				player.CurrentDirection = MovementDown;
				player.turnDir = 0;
				break;
			}
			if(game.checkCollision( topBox, tiles[i]->getBox() ) && game.checkCollision( topBox2, tiles[i]->getBox() ) && player.turnDir == 1 && tiles[i]->getType() == 0 )
			{
				player.CurrentDirection = MovementUp;
				player.turnDir = 0;
				break;
			}
			if(game.checkCollision( leftBox, tiles[i]->getBox() ) && game.checkCollision( leftBox2, tiles[i]->getBox() ) && player.turnDir == 4 && tiles[i]->getType() == 0 )
			{
				player.CurrentDirection = MovementLeft;
				player.turnDir = 0;
				break;
			}
			if(game.checkCollision( rightBox, tiles[i]->getBox() ) && game.checkCollision( rightBox2, tiles[i]->getBox() ) && player.turnDir == 2 && tiles[i]->getType() == 0 )
			{
				player.CurrentDirection = MovementRight;
				player.turnDir = 0;
				break;
			}

		}
		for(int i  = 0; i < coins.size(); i++)
		{
			if(game.checkCollision(player.getPlayerBox(), coins[i].getBox()) && !coins[i].dead)
			{
				LTexture emptyTex;
				emptyTex.loadFromFile( "Data/Art/empty.png", scr.getRenderer() );
				coins[i].tileTex = &emptyTex;
				coins[i].dead = true;
				player.score += 10;
			}
		}
		
		if( player.getPlayerX() + player.getPlayerBox().w <= 0 && player.CurrentDirection == MovementLeft)
		{
			player.playerBox.x = SCREEN_WIDTH - 1;
		}
		if( player.getPlayerX() >= SCREEN_WIDTH && player.CurrentDirection == MovementRight )
		{
			player.playerBox.x = 1 - player.getPlayerBox().w;
		}

		anim++;
		if(anim == 420)
			anim = 0;

//	//	// RENDERING // // //         //	//	// RENDERING // // //  	//	//	// RENDERING // // //  //	//	// RENDERING // // //   //	//	// RENDERING // // //  

			SDL_Color textColor = { 0xff, 0x00, 0xBA }; 
			SDL_Rect textRect = {200, 0, 64, 32};
			char* pScore = new char[6];
			sprintf(pScore, "%d", player.score);
			std::string pScoreStr;
			for(int i = 0; i < 3; ++i)	
			{
				pScoreStr.push_back(pScore[i]);
			}
			scoreTex.loadFromRenderedText("SCORE :  " + pScoreStr, textColor, scr.getRenderer(), menu.font);

			SDL_SetRenderDrawColor( scr.getRenderer(), 0x00, 0x00, 0x00, 0x00 );
			SDL_RenderClear( scr.getRenderer() );
			


			//"SCORE :  " + pScoreStr



			for(int i = 0; i < 400; i++) {
				//printf( "%d = %d \n ", i, tiles[i]->getType());
				tiles[i]->show(scr.getRenderer());
			}

			for( int i = 0; i < coins.size(); ++i)
			{
				coins[i].show( scr.getRenderer() );
			}

			bool pace = anim % 20 > 10; 

			if(player.CurrentDirection == MovementLeft || player.CurrentDirection == MovementRight)
			{
				if(pace)
				{
					player.setPlayerTex(&playerTextures[0]);
				}
				else
				{
					player.setPlayerTex(&playerTextures[1]);
				}
				if(player.CurrentDirection == MovementRight)
					player.render(scr.getRenderer(), SDL_FLIP_NONE , 32, 32);
				if(player.CurrentDirection == MovementLeft)
					player.render(scr.getRenderer(), SDL_FLIP_HORIZONTAL , 32, 32);
			}

			if(player.CurrentDirection == MovementDown || player.CurrentDirection == MovementUp)
			{
				if(pace)
				{
					player.setPlayerTex(&playerTextures[2]);
				}
				else
				{
					player.setPlayerTex(&playerTextures[3]);
				}
				if(player.CurrentDirection == MovementUp)
					player.render(scr.getRenderer(), SDL_FLIP_NONE , 32, 32);
				if(player.CurrentDirection == MovementDown)
					player.render(scr.getRenderer(), SDL_FLIP_VERTICAL , 32, 32);
			}

			//SpriteSheetTexture.NewRender(player.playerBox.x, player.playerBox.y, currentClip, gRenderer);
			scoreTex.render(0, 0, scr.getRenderer(), SDL_FLIP_NONE, 150, 40);
			SDL_RenderPresent( scr.getRenderer() );

			float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}
			++countedFrames;

			int frameTicks = capTimer.getTicks();
			if( frameTicks < SCREEN_TICK_PER_FRAME )
			{
				SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
			}

	}
	
	
	//system("pause");
	return 0;
}

