#include "SoundMng.h"

USING_NS_CC;

std::unique_ptr<SoundMng, SoundMng::SoundMngDeleter> SoundMng::s_instance(new SoundMng());

void SoundMng::Init()
{
}

CkSound* SoundMng::OnceSoundPlay(const char* filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string resources = "Resources/" + std::string(filename);
	CkBank* bank = CkBank::newBank(resources.c_str());
#else
	CkBank* bank = CkBank::newBank(filename);
#endif
	CkSound* sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(0);
	sound->play();
	return sound;
}

CkSound* SoundMng::SoundLoopPlay(const char * filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string resources = "Resources/" + std::string(filename);
	CkBank* bank = CkBank::newBank(resources.c_str());
#else
	CkBank* bank = CkBank::newBank(filename);
#endif
	CkSound* sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(-1);
	sound->play();
	return sound;
}

void SoundMng::Update()
{
	CkUpdate();
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}
