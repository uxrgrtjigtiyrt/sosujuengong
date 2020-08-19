#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <map>

#ifndef DSBCAPS_CTRLDEFAULT  //DX6.0���� ���� ���������Ƿ� define����
#define DSBCAPS_CTRLDEFAULT  (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME)
#endif

//�Է°��� dB(decibel)�� �ٲ��ִ� ��ũ�� �Լ�
#define DSVOLUME_TO_DB(volume)   ((DWORD)(-30*(100-volume)))

//��ó : https://202psj.tistory.com/88

class SoundManager
{
private :
	LPDIRECTSOUND8  g_lpDS = NULL;  //���̷�Ʈ ���尳ü
	BOOL g_bPlay = FALSE;
	std::map<const char*, LPDIRECTSOUNDBUFFER *> soundMap;
public :
	SoundManager();
	~SoundManager();

	BOOL CreateDirectSound(HWND hWnd);
	BOOL LoadWave(const char* lpFileName, const char* soundName);
	BOOL SetVolume(LPDIRECTSOUNDBUFFER lpDSBuffer, LONG lVolume);
	BOOL SetPan(LPDIRECTSOUNDBUFFER lpDSBuffer, LONG lPan);

	void DeleteDirectSound();
	void Play(const char* soundName, BOOL Loop);
	void Stop(const char* soundName);
};