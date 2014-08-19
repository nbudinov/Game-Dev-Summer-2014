	#include <SDL.h>

class Player;
class Tile;
class Screen;
class Mobs;

class Game
{
public:

	Game();

	bool init();

	bool loadMedia();

	bool loadGhosts(Mobs* ghosts[]);

	bool setTiles( Tile* tiles[] );

	//bool ifNextTileCollides(Player player, Tile *tiles[]);

	//bool ifTileCollidable(int x, int y, Tile* tiles[]);

	bool checkCollision( SDL_Rect A, SDL_Rect B );

	int PlayerCollision( Player* player, Tile* tiles[]);

	int Collision( Player player, Tile* tiles[]);

	int GhostsCollision( Mobs* ghosts[], Tile* tiles[] );

	void chase(Player player, Mobs* ghost );

	void changeMobDir(Mobs* ghost);

	void GhostsAI(Player player, Mobs *ghosts[], Tile* tiles[]);

	SDL_Renderer* getRenderer();

	bool loadEmptyTex(Screen screen);

private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

};
