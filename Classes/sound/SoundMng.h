#pragma once
#include "cocos2d.h"
#include "ck/ck.h"
#include "ck/bank.h"
#include "ck/sound.h"
//#include <jni.h>
#define lpSoundMng SoundMng::GetInstance()

//#ifndef __ANDROID_JNI__
//#define __ANDROID_JNI__
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(
//		JNIEnv * env,
//		jclass activity,
//		jobject context
//	);
//#ifdef __cplusplus
//}
//#endif // __cplusplus
//#endif


class SoundMng
{
public:
	static SoundMng& GetInstance()
	{
		return *s_instance;	
	}
	void Init();
	void OnceSoundPlay(const char* filename);
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

