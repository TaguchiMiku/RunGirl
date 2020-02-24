#pragma once
#include "cocos2d.h"
#include "ck/ck.h"
#include "ck/bank.h"
#include "ck/sound.h"
#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	static SoundMng& GetInstance()
	{
		return *s_instance;	
	}
	void Init();
	CkSound* OnceSoundPlay(const char* filename);
	CkSound* SoundLoopPlay(const char* filename);
	void Update();
private:
	struct SoundMngDeleter
	{
		void operator()(SoundMng* sndMng) const
		{
			delete sndMng;
		}
	};
	SoundMng();
	~SoundMng();

	static std::unique_ptr<SoundMng, SoundMngDeleter> s_instance;
};

