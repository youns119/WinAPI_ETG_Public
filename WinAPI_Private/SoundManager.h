#pragma once

#include "Singleton.h"

#include "Channel.h"

class CSoundManager : public Singleton<CSoundManager>
{
public :
	CSoundManager();
	virtual ~CSoundManager();

public:
	void Init();
	void Release();

public :
	void PlaySound(const TCHAR* _pSoundKey, CHANNELID _eID, float _fVolume);
	void PlayBGM(const TCHAR* _pSoundKey, float _fVolume);
	void PlayBGMOnce(const TCHAR* _pSoundKey, CHANNELID _eID, float _fVolume);
	void StopSound(CHANNELID _eID);
	void StopAll();
	void SetChannelVolume(CHANNELID _eID, float _fVolume);

private:
	void LoadSoundFile();

private:
	map<const TCHAR*, FMOD::Sound*> m_mapSound;
	FMOD::Channel* m_pChannelArr[(UINT)CHANNELID::MAXCHANNEL];
	FMOD::System* m_pSystem;
};