#ifndef AUDIOFILE_H
#define AUDIOFILE_H
#include <string>
class AudioFile
{
public:
	AudioFile();
	virtual ~AudioFile();
	void SetMasterVolume(const int MasterVolume) const;
	int GetMasterVolume() const;
	//virtuals
	virtual bool Load(const std::string& FileName) = 0;
	virtual void Play(const int LoopCount = 0) const = 0;
	virtual void SetVolume(int Volume) const = 0;
	virtual void Destroy() = 0;
};

#endif