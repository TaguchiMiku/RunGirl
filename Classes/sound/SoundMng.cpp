#include "SoundMng.h"

USING_NS_CC;

std::unique_ptr<SoundMng, SoundMng::SoundMngDeleter> SoundMng::s_instance(new SoundMng());

#if CK_PLATFORM_ANDROID
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv * env, jclass activity, jobject context)
{
	CkConfig config;
	CkInit(&config);
	CkBank* bank = CkBank::newBank("Resources/sound/bgm1.ckb", kCkPathType_FileSystem);
	CkSound* sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(-1);
	sound->play();
}
#ifdef __cplusplus
}
#endif
#endif

void SoundMng::Init()
{
	CkConfig config;
	CkInit(&config);
}

void SoundMng::OnceSoundPlay(const char* filename)
{
	CkBank* bank = CkBank::newBank(filename);
	CkSound* sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(0);
	sound->play();
}

CkSound* SoundMng::SoundLoopPlay(const char * filename)
{
	CkBank* bank = CkBank::newBank(filename);
	CkSound* sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(-1);
	sound->play();
	return sound;
}

void SoundMng::Update()
{
	CkUpdate();
	Sleep(30);
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}
