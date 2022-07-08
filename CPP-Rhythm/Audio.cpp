#include "Audio.h"

Audio::Audio()
{
	memset(&openParms, 0, sizeof(openParms));
	memset(&playParms, 0, sizeof(playParms));
}

Audio::~Audio()
{
}

void Audio::Open(wstring fileName)
{
	openParms.lpstrElementName = fileName.c_str();
	openParms.lpstrDeviceType = L"mpegvideo";
	openParms.wDeviceID = 0;
	
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_SHAREABLE, (DWORD_PTR)&openParms));
}

void Audio::Close()
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_CLOSE, 0, 0));
}

void Audio::Play()
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playParms));
}

void Audio::Stop()
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_STOP, 0, 0));
}

void Audio::Pause()
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_PAUSE, 0, 0));
}

void Audio::Resume()
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_RESUME, 0, 0));
}

void Audio::SetVolume(int volume)
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_DGV_SETAUDIO_VOLUME, MCI_DGV_SETAUDIO_VALUE, (DWORD_PTR)&volume));
}

void Audio::SetPosition(int position)
{
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START | MCI_SEEK_TO_END, (DWORD_PTR)&position));
}

int Audio::GetPosition()
{
	MCI_STATUS_PARMS statusParms;
	statusParms.dwItem = MCI_STATUS_POSITION;
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParms));
	return statusParms.dwReturn;
}

bool Audio::IsPlaying()
{
	MCI_STATUS_PARMS statusParms;
	statusParms.dwItem = MCI_STATUS_MODE;
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParms));
	return statusParms.dwReturn == MCI_MODE_PLAY;
}

int Audio::GetLength()
{
	MCI_STATUS_PARMS statusParms;
	statusParms.dwItem = MCI_STATUS_LENGTH;
	showMciError(mciSendCommand(openParms.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParms));
	return statusParms.dwReturn;
}

void Audio::showMciError(DWORD dwError)
{
	if (dwError == 0) return;
	
	wchar_t szErrorBuf[MAXERRORLENGTH];
	MessageBeep(MB_ICONEXCLAMATION);
	if (mciGetErrorString(dwError, (LPWSTR)szErrorBuf, MAXERRORLENGTH))
	{
		MessageBox(0, szErrorBuf, L"Error", MB_OK);
	}
	else
	{
		MessageBox(0, L"Unknown Error", L"Error", MB_OK);
	}
}