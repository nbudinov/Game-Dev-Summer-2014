#include "SoundEffects.h"
#include <stdio.h>


SoundEffects::SoundEffects(void)
{
}


SoundEffects::~SoundEffects(void)
{
	Mix_FreeMusic(music);
	music = NULL;

	Mix_Quit();
}

bool SoundEffects::loadMedia()
{


	return true;
}

void SoundEffects::playSound(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}

void SoundEffects::playMusic(Mix_Music* music)
{
	if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( music, -1 );
    }
}


Mix_Music* SoundEffects::getMusic()
{
	return SoundEffects::music;
}

