#pragma once

#include <SDL_mixer.h>
#include <SDL.h>

class SoundEffects
{
public:
	SoundEffects(void);
	~SoundEffects(void);

	bool loadMedia();

	void playSound(Mix_Chunk* sound);

	void playMusic(Mix_Music* music);

	Mix_Music* getMusic();

private:

	Mix_Music* music;

};

