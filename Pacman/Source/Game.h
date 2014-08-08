#include <SDL.h>

class Player;
class Tile;

class Game
{
public:

	bool checkCollision( SDL_Rect A, SDL_Rect B );

	int Collision( Player player, Tile* tiles[] );
};