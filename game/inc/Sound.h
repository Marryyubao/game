#pragma once

#ifndef _SOUND_H_
#define _SOUND_H_

#include"3rd-party/fmod.hpp"

struct FmodSound
{
	FMOD::Sound* snd;//具体播放的声音
	FMOD::Channel* ch1;//频道

	FmodSound() :snd(nullptr), ch1(nullptr) {}
	~FmodSound()
	{
		if (snd)
		{
			snd->release();
		}
	}
};

void InitFmodSystem();
void UpdateFmodSystem();
void CloseFmodSystem();

void LoadFmodSound(FmodSound* pSound, const char* filename);//Fmode接口不支持unicode
void PlayFmodSound(FmodSound* pSound, bool share = false);

//引入文件库
#pragma comment(lib,"lib/fmod_vc.lib")

#endif