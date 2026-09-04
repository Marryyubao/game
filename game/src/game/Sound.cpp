#include"../../inc/Sound.h"

static FMOD::System* system = nullptr;//管理所有FMOD音频的对象（通过指针访问）
static FMOD::Channel* sharedChannel = nullptr;//共享的频道

void InitFmodSystem()
{
	FMOD::System_Create(&system);
	system->init(321, FMOD_INIT_NORMAL, nullptr);

}
void UpdateFmodSystem()
{
	if (system)
	{
		system->update();
	}
}
void CloseFmodSystem()
{
	if (system)
	{
		system->close();
		system->release();
	}
}

void LoadFmodSound(FmodSound* pSound, const char* filename)//Fmode接口不支持unicode
{
	system->createSound(filename, FMOD_DEFAULT, nullptr, &(pSound->snd));
}
void PlayFmodSound(FmodSound* pSound, bool share)
{
	if (share)
	{
		system->playSound(pSound->snd, nullptr, false, &sharedChannel);//如果共享则在这个频道上播放
	}
	else
	{
		bool isPlaying = false;
		if (pSound->ch1)
		{
			pSound->ch1->isPlaying(&isPlaying);
		}
		if (!isPlaying)
		{
			system->playSound(pSound->snd, nullptr, false, &(pSound->ch1));
		}
	}
}