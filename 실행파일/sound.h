#pragma once
#include "pch.h"
#define BGM "asset/sound/pacman_eatgem.wav"    //BGM 경로 지정
#define BGM2 "asset/sound/pacman_death.wav"    //BGM 경로 지정
class SOUND
{
	MCI_PLAY_PARMS playEatBgm;
	MCI_OPEN_PARMS openEatBgm;
	int dwID;

	MCI_PLAY_PARMS playDieBgm;
	MCI_OPEN_PARMS openDieBgm;
	int dwID2;


public:
	void playingEatSound(void) {
		openEatBgm.lpstrElementName = TEXT(BGM);    //파일 오픈
		openEatBgm.lpstrDeviceType = TEXT("waveaudio");    //mp3 형식
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openEatBgm);
		dwID = openEatBgm.wDeviceID;
		//Sleep(300);    //효과음이 재생될 때까지 정지했다가
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //음원 재생 위치를 처음으로 초기화
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openEatBgm);    //음악을 한 번 재생
	}
	void playingDietSound(void) {
		openDieBgm.lpstrElementName = TEXT(BGM2);    //파일 오픈
		openDieBgm.lpstrDeviceType = TEXT("waveaudio");    //mp3 형식
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDieBgm);
		dwID = openDieBgm.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openDieBgm);    //음악을 한 번 재생
		Sleep(1200); //효과음이 재생될 때까지 정지했다가
		//mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //음원 재생 위치를 처음으로 초기화
	}
};

