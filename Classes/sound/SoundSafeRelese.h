#pragma once
#include <cricket-1.6.7/inc/ck/sound.h>
struct SoundSafeRelese
{
	void operator()(CkSound* sound)
	{
		if (sound)
		{
			sound->destroy();
			sound = nullptr;
		}
	}
};
