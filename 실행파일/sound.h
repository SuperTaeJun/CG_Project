#pragma once
#include "pch.h"
#define BGM "asset/sound/pacman_eatgem.wav"    //BGM ��� ����
#define BGM2 "asset/sound/pacman_death.wav"    //BGM ��� ����
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
		openEatBgm.lpstrElementName = TEXT(BGM);    //���� ����
		openEatBgm.lpstrDeviceType = TEXT("waveaudio");    //mp3 ����
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openEatBgm);
		dwID = openEatBgm.wDeviceID;
		//Sleep(300);    //ȿ������ ����� ������ �����ߴٰ�
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openEatBgm);    //������ �� �� ���
	}
	void playingDietSound(void) {
		openDieBgm.lpstrElementName = TEXT(BGM2);    //���� ����
		openDieBgm.lpstrDeviceType = TEXT("waveaudio");    //mp3 ����
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openDieBgm);
		dwID = openDieBgm.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openDieBgm);    //������ �� �� ���
		Sleep(1200); //ȿ������ ����� ������ �����ߴٰ�
		//mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
	}
};

