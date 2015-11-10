#include "AudioFile.h"
#include "SDL_mixer.h"

AudioFile::AudioFile(){}

AudioFile::~AudioFile(){}

void AudioFile::SetMasterVolume(const int MasterVolume) const{
	Mix_Volume(-1, MasterVolume);
}

int AudioFile::GetMasterVolume() const{
	return Mix_Volume(-1, -1);
}
