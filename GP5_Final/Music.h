#ifndef MUSIC_H
#define MUSIC_H
#include "AudioFile.h"
#include<string>

//forward declaration
struct _Mix_Music;

class Music : public AudioFile
{
public:
	Music();
	Music(const Music&) = delete;
	Music(Music&&) = delete;
	Music& operator=(const Music&) = delete;
	Music& operator=(Music&&) = delete;
	~Music();

	virtual bool Load(const std::string& FileName) override;
	virtual void Play(const int LoopCount = 0) const override;
	virtual void SetVolume(int Volume) const override;
	virtual void Destroy() override;
	void Stop() const;
	void Pause() const;
	void Resume() const;
	void TogglerPause() const;

private:
	_Mix_Music* MixMusic;
};

#endif
