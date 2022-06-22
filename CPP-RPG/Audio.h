#pragma once
#include "GlobalStd.h"
#include <Mmsystem.h>
#include <mciapi.h>
#include <Digitalv.h>

class Audio
{
public:
	Audio();
	~Audio();
	
private:
	void showMciError(DWORD dwError);
	
	MCI_OPEN_PARMS openParms;
	MCI_PLAY_PARMS playParms;
	
public:
	void Open(wstring fileName);
	void Close();
	void Play();
	void Stop();
	void Pause();
	void Resume();
	void SetVolume(int volume);
	void SetPosition(int position);
	int GetPosition();
	bool IsPlaying();
};

