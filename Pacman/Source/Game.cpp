#include "Game.h"
#include "Tile.h"
#include "LTexture.h"
#include "Screen.h"
#include<fstream>

Screen screen;

Game::Game()
{
	if( !wallTexture.loadFromFile("images/wall.bmp", screen.getRenderer()) ){
		printf("cant load wall.png ");
	}

	if( !emptyTexture.loadFromFile("images/empty.bmp", screen.getRenderer()) ){
		printf("cant load empty.png ");
	}
}

bool Game::setTiles( Tile* tiles[] )
{
		
    int x = 0, y = 0;

    std::ifstream map( "images/map.txt" );

    if( map == NULL )
    {
        return false;
    }



}
