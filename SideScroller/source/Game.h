#include <SDL.h>

class Player;
class Tile;

class Game
{
public:
	bool check_collision( SDL_Rect A, SDL_Rect B );

	int Collision(Player player, Tile* tiles[]);

	bool setTiles(Tile *tiles[]);

};