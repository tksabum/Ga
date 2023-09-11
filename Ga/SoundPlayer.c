#include "SoundPlayer.h"

FMOD_SYSTEM* fmod_system = 0;
void* extradriverdata = 0;

FMOD_SOUND* sound[128];
FMOD_CHANNEL* bgmChannel;
FMOD_CHANNEL* effectChannel[127];

float bgmVolume;
float effectVolume;

void SoundPlayer_Ready()
{
	FMOD_System_Create(&fmod_system);
	FMOD_System_Init(fmod_system, 32, FMOD_INIT_NORMAL, extradriverdata);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_MAIN, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_MAIN]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_ROOM1, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_ROOM1]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_ROOM2, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_ROOM2]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_ROOM3, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_ROOM3]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_ROOM4, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_ROOM4]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_SETTING, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_SETTING]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_VERYDANGERTIME, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_VERYDANGERTIME]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_MAINMENU, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_MAINMENU]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_ENDING, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_ENDING]);
	FMOD_System_CreateSound(fmod_system, NAME_BGM_SAMPLE04, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_SAMPLE04]);

	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_BUTTON, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_BUTTON]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_GAMEOVER, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_GAMEOVER]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_JUMP, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_JUMP]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_DASH, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DASH]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_BREAK, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_BREAK]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_DOORCLOSE, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DOORCLOSE]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_CRAWBAR, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_CRAWBAR]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_GHOST1, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_GHOST1]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_DANGERTIME, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DANGERTIME]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_VERYDANGERTIMER, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_VERYDANGERTIME]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_PAPERGRAB, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_PAPERGRAB]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_CUTTINGBED, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_CUTTINGBED]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_CLOSETSOUND, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_CLOSETSOUND]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_GLASSBREAK, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_GLASSBREAK]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_CLOSETSOUND2, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_CLOSETSOUND2]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_DOOROPEN, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DOOROPEN]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_GHOSTJUMPSCARE, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_GHOSTJUMPSCARE]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE1DRAWER, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE1DRAWER]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_DOOROPEN, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DOOROPEN]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_MOVINGOBJECT, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_MOVINGOBJECT]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_PHOTOCLOSEUP, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_PHOTOCLOSEUP]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_NEWSPAPER, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_NEWSPAPER]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STEPIN, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STEPIN]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STARTGAME, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STARTGAME]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE1BIGFACE, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE1BIGFACE]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_WOMAN_CRYING, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_WOMAN_CRYING]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_CLOSEUPTEXT, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_CLOSEUPTEXT]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_JUMPSCAREJ, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_JUMPSCAREJ]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_PHOTOCHANGE, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_PHOTOCHANGE]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_CUTSCENE01, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_CUTSCENE01]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_CUTSCENE02, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_CUTSCENE02]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_CUTSCENE03, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_CUTSCENE03]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_CUTSCENE04, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_CUTSCENE04]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_CLOSEUP, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_CLOSEUP]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_STAGE4_FRONT, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_STAGE4_FRONT]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_LOCKEDDOOR, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_LOCKEDDOOR]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_SOFAGHOST, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_SOFAGHOST]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_SAMPLE13, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_SAMPLE13]);
	FMOD_System_CreateSound(fmod_system, NAME_EFFECT_SAMPLE14, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_SAMPLE14]);


	bgmVolume = 1.0f;
	effectVolume = 1.0f;

	//FMOD_RESULT fmod_result = FMOD_Channel_SetVolume(channelSample, 0.1f);
}

void SoundPlayer_StopAll()
{
	FMOD_Channel_Stop(bgmChannel);

	for (int i = 0; i < 127; i++)
	{
		FMOD_Channel_Stop(effectChannel[i]);
	}

}

void SoundPlayer_StopAllBGM()
{
	FMOD_Channel_Stop(bgmChannel);
}

void SoundPlayer_Play(int soundNum)
{
	if (SOUND_BGM_BEGIN <= soundNum && soundNum < SOUND_BGM_END)
	{
		FMOD_BOOL isPlaying;
		FMOD_Channel_IsPlaying(bgmChannel, &isPlaying);
		if (isPlaying)
		{
			FMOD_Channel_Stop(bgmChannel);
		}
		FMOD_System_PlaySound(fmod_system, sound[soundNum], 0, 0, &bgmChannel);
		FMOD_Channel_SetVolume(bgmChannel, bgmVolume);
	}

	if (SOUND_EFFECT_BEGIN <= soundNum && soundNum < SOUND_EFFECT_END)
	{
		for (int i = 0; i < 127; i++)
		{
			FMOD_BOOL isPlaying;
			FMOD_RESULT result = FMOD_Channel_IsPlaying(effectChannel[i], &isPlaying);
			if (result != FMOD_OK || !isPlaying)
			{
				FMOD_System_PlaySound(fmod_system, sound[soundNum], 0, 0, &effectChannel[i]);
				FMOD_Channel_SetVolume(effectChannel[i], effectVolume);
				break;
			}
		}
	}
}

void SoundPlayer_SetBgmVolume(float volume)
{
	bgmVolume = volume;

	if (bgmVolume > 1.0f)
	{
		bgmVolume = 1.0f;
	}

	if (bgmVolume < 0.0f)
	{
		bgmVolume = 0.0f;
	}

	FMOD_Channel_SetVolume(bgmChannel, bgmVolume);
}

void SoundPlayer_SetEffectVolume(float volume)
{
	effectVolume = volume;

	if (effectVolume > 1.0f)
	{
		effectVolume = 1.0f;
	}

	if (effectVolume < 0.0f)
	{
		effectVolume = 0.0f;
	}
}

void SoundPlayer_BgmVolumeUp()
{
	bgmVolume += 0.1f;
	if (bgmVolume > 1.0f)
	{
		bgmVolume = 1.0f;
	}
	FMOD_Channel_SetVolume(bgmChannel, bgmVolume);
}

void SoundPlayer_BgmVolumeDown()
{
	bgmVolume -= 0.1f;
	if (bgmVolume < 0.0f)
	{
		bgmVolume = 0.0f;
	}
	FMOD_Channel_SetVolume(bgmChannel, bgmVolume);
}

void SoundPlayer_EffectVolumeUp()
{
	effectVolume += 0.1f;
	if (effectVolume > 1.0f)
	{
		effectVolume = 1.0f;
	}
}

void SoundPlayer_EffectVolumeDown()
{
	effectVolume -= 0.1f;
	if (effectVolume < 0.0f)
	{
		effectVolume = 0.0f;
	}
}

float SoundPlayer_GetBgmVolume()
{
	return bgmVolume;
}

float SoundPlayer_GetEffectVolume()
{
	return effectVolume;
}
