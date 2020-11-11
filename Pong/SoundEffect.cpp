#include"SoundEffect.h"

SoundEffect::SoundEffect(const char* pFilename)
	:filename(pFilename), sound(nullptr)
{}
void SoundEffect::load()
{
	sound = Mix_LoadWAV(filename);
}
void SoundEffect::play()
{
	Mix_PlayChannel(-1, sound, 0);
}
SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(sound);
}